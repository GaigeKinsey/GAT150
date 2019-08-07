#include "scene.h"
#include "entity.h"
#include "sprite_component.h"
#include "controller_component.h"
#include "physics_component.h"

bool Scene::Create(const Name& name, Engine* engine)
{
	m_name = name;
	m_engine = engine;

	m_component_factory = new ComponentFactory;
	m_component_factory->Register("sprite_component", new Creator<SpriteComponent, Component>());
	m_component_factory->Register("controller_component", new Creator<ControllerComponent, Component>());
	m_component_factory->Register("physics_component", new Creator<PhysicsComponent, Component>());

	return true;
}

void Scene::Destroy()
{
	for (Entity* entity : m_entities) {
		entity->Destroy();
		delete entity;
	}

	m_entities.clear();

	delete m_component_factory;
}

bool Scene::Load(const rapidjson::Value& value)
{
	const rapidjson::Value& entities_value = value["entities"];
	if (entities_value.IsArray()) {
		LoadEntities(entities_value);
	}

	return true;
}

void Scene::Update()
{
	for (Entity* entity : m_entities) {
		entity->Update();

		if (entity->m_transform.translation.x < 0.0f) entity->m_transform.translation.x = 800.0f;
		if (entity->m_transform.translation.x > 800.0f) entity->m_transform.translation.x = 0.0f;
		if (entity->m_transform.translation.y > 600.0f) entity->m_transform.translation.y = 0.0f;
		if (entity->m_transform.translation.y < 0.0f) entity->m_transform.translation.y = 600.0f;
	}

}

void Scene::Draw()
{
	for (Entity* entity : m_entities) {
		entity->Draw();
	}
}

void Scene::Add(Entity* entity)
{
	ASSERT(entity);
	ASSERT(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());

	m_entities.push_back(entity);
}

std::list<Entity*>::iterator Scene::Remove(Entity* entity, bool destroy)
{
	ASSERT(entity);

	auto next_iter = m_entities.end();

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end()) {
		if (destroy) {
			(*iter)->Destroy();
			delete* iter;
			next_iter = m_entities.erase(iter);
		}
	}

	return next_iter;
}

Entity* Scene::GetEntityWithName(const Name& name)
{
	Entity* entity = nullptr;

	for (Entity* _entity : m_entities) {
		if (_entity->GetName() == name) {
			entity = _entity;
			break;
		}
	}

	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const Name& tag)
{
	std::vector<Entity*> entities;
	for (Entity* entity : m_entities) {
		if (entity->GetTag() == tag) {
			entities.push_back(entity);
		}
	}

	return entities;
}

bool Scene::LoadEntities(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& entity_value = value[i];
		if (entity_value.IsObject()) {
			Entity* entity = new Entity(this);
			if (entity->Load(entity_value)) {
				Add(entity);
			}
			else {
				delete entity;
				return false;
			}
		}
	}

	return true;
}
