#pragma once
#include "object.h"

class Entity;

class Component : public Object
{
public:
	Component(const Name& name, Entity* owner) : Object(name), m_owner(owner) {}

	virtual void Update() = 0;

	Entity* GetOwner() { return m_owner; }

protected:
	Entity* m_owner;
};