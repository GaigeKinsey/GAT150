#include "entity.h"
#include "component.h"
#include "render_component.h"

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
	return false;
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
