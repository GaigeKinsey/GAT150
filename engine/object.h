#pragma once
#include "..\\core\name.h"
#include "..\\core\json.h"

class Object
{
public:
	Object() {}

	virtual void Destroy() = 0;
	virtual bool Load(const rapidjson::Value& value) = 0;

	const Name& GetName() { return m_name; }

protected:
	Name m_name;
};