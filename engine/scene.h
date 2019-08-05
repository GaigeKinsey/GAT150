#pragma once
#include "object.h"
#include <list>

class Engine;
class Entity;

class Scene : public Object
{
public:
	Scene(const Name& name, Engine* engine) : Object(name), m_engine(engine) { }

	bool Create() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	void Update();
	void Draw();
	
	void Add(Entity* entity);
	std::list<Entity*>::iterator Remove(Entity* entity, bool destroy = true);

	Entity* GetEntityWithName(const Name& name);
	std::vector<Entity*> GetEntitiesWithTag(const Name& tag);

	Engine* GetEngine() { return m_engine; }

protected:
	Engine* m_engine;

	std::list<Entity*> m_entities;
};