#pragma once
#include "..\\core\name.h"
#include "..\\core\json.h"

class Object
{
public:
	Object(const Name& name) : m_name(name) {}
	
	virtual bool Create() = 0;
	virtual void Destroy() = 0;
	virtual bool Load(const rapidjson::Value& value) = 0;

	const Name& GetName() { return m_name; }

protected:
	Name m_name;
};