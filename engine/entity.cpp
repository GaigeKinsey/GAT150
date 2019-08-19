#include "entity.h"
#include "scene.h"
#include "component.h"
#include "render_component.h"

Entity::Entity(const Entity& entity)
{
	m_name = entity.m_name;
	m_tag = entity.m_tag;
	m_scene = entity.m_scene;
	m_spawner = entity.m_spawner;
	m_transform = entity.m_transform;

	for (Component* component : entity.m_components) {
		Component* clone_component = dynamic_cast<Component*>(component->Clone());
		AddComponent(clone_component);
	}
}

bool Entity::Create(const Name& name, Scene* scene)
{
	m_name = name;
	m_scene = scene;

	return true;
}

void Entity::Destroy()
{
	for (Component* component : m_components) {
		component->Destroy();
		delete component;
	}

	m_components.clear();
}

bool Entity::Load(const rapidjson::Value& value)
{
	json::get_name(value, "name", m_name);
	json::get_name(value, "tag", m_tag);
	json::get_bool(value, "spawner", m_spawner);

	const rapidjson::Value& transform_value = value["transform"];
	if (transform_value.IsObject()) {
		m_transform.Load(transform_value);
	}

	const rapidjson::Value& component_value = value["components"];
	if (component_value.IsArray()) {
		LoadComponents(component_value);
	}

	return true;
}

void Entity::Initialize()
{
	for (Component* component : m_components) {
		component->Initialize();
	}
}

void Entity::Update()
{
	for (Component* component : m_components) {
		component->Update();
	}
}

void Entity::Draw()
{
	m_transform.update();
	RenderComponent* component = GetComponent<RenderComponent>();
	if (component) {
		component->Draw();
	}
}

void Entity::AddComponent(Component* component)
{
	ASSERT(component);
	ASSERT(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	component->SetOwner(this);
	m_components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
	ASSERT(component);
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end()) {
		(*iter)->Destroy();
		delete *iter;
		m_components.erase(iter);
	}
}

bool Entity::LoadComponents(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& component_value = value[i];
		if (component_value.IsObject()) {
			Name type;
			json::get_name(component_value, "type", type);
			Component* component = m_scene->GetObjectFactory()->Create<Component>(type);
			if (component && component->Load(component_value)) {
				AddComponent(component);
			}
		}
	}

	return true;
}
