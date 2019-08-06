#pragma once
#include "object.h"
#include "entity.h"

class Entity;

class Component : public Object
{
public:
	Component() {}

	void Create(const Name& name, Entity* owner) {
		m_name = name;
		m_owner = owner;
	}
	virtual void Update() = 0;

	Entity* GetOwner() { return m_owner; }

protected:
	Entity* m_owner = nullptr;
};