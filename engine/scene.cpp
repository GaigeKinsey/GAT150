#include "scene.h"
#include "entity.h"
#include "sprite_component.h"
#include "controller_component.h"

bool Scene::Create(const Name& name, Engine* engine)
{
	m_name = name;
	m_engine = engine;

	m_component_factory = new ComponentFactory;
	m_component_factory->Register("sprite_component", new Creator<SpriteComponent, Component>());
	m_component_factory->Register("controller_component", new Creator<ControllerComponent, Component>());

	Entity* entity = new Entity();
	entity->Create("entity", this);
	entity->m_transform.scale = vector2::one;

	{
		SpriteComponent* component = m_component_factory->Create<SpriteComponent>("sprite_component");
		component->Create("component", entity, "textures/ghost.bmp");
		entity->AddComponent(component);
	}
	{
		ControllerComponent* component = m_component_factory->Create<ControllerComponent>("controller_component");
		component->Create("component", entity);
		entity->AddComponent(component);
	}

	Add(entity);

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
