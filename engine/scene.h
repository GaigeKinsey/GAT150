#pragma once
#include "object.h"
#include "component.h"
#include "..\\framework\factory.h"
#include <list>

class Engine;
class Entity;

class ComponentFactory : public Factory<Component, Name> {};

class Scene : public Object
{
public:
	Scene() : m_engine(nullptr), m_component_factory(nullptr) {}

	bool Create(const Name& name, Engine* engine);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	void Update();
	void Draw();
	
	void Add(Entity* entity);
	std::list<Entity*>::iterator Remove(Entity* entity, bool destroy = true);

	Entity* GetEntityWithName(const Name& name);
	std::vector<Entity*> GetEntitiesWithTag(const Name& tag);

	Engine* GetEngine() { return m_engine; }
	ComponentFactory* GetComponentFactory() { return m_component_factory; }

protected:
	bool LoadEntities(const rapidjson::Value& value);

protected:
	Engine* m_engine = nullptr;
	ComponentFactory* m_component_factory = nullptr;
	std::list<Entity*> m_entities;
};