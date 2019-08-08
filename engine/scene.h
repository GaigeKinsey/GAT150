#pragma once
#include "object.h"
#include "..\\framework\factory.h"
#include <list>

class Engine;
class Entity;

class ObjectFactory : public Factory<Object, Name> {};

class Scene : public Object
{
public:
	Scene() : m_engine(nullptr), m_object_factory(nullptr) {}

	bool Create(const Name& name, Engine* engine);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Scene* Clone() override { return new Scene(*this); }

	void Update();
	void Draw();
	
	void Add(Entity* entity);
	std::list<Entity*>::iterator Remove(Entity* entity, bool destroy = true);

	Entity* GetEntityWithName(const Name& name);
	std::vector<Entity*> GetEntitiesWithTag(const Name& tag);

	Engine* GetEngine() { return m_engine; }
	ObjectFactory* GetComponentFactory() { return m_object_factory; }

protected:
	bool LoadEntities(const rapidjson::Value& value);

protected:
	Engine* m_engine = nullptr;
	ObjectFactory* m_object_factory = nullptr;
	std::list<Entity*> m_entities;
};