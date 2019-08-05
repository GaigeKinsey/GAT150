#include "scene.h"
#include "entity.h"

bool Scene::Create()
{
	return true;
}

void Scene::Destroy()
{
	for (Entity* entity : m_entities) {
		entity->Destroy();
		delete entity;
	}

	m_entities.clear();
}

bool Scene::Load(const rapidjson::Value& value)
{
	return false;
}

void Scene::Update()
{
	for (Entity* entity : m_entities) {
		entity->Update();
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

	return nullptr;
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
