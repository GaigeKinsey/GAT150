#pragma once
#include "..\\core\name.h"
#include "..\\core\json.h"
#include "..\\framework\event_dispatcher.h"

class Object
{
public:
	Object() {}

	virtual void Destroy() = 0;
	virtual bool Load(const rapidjson::Value& value) = 0;
	virtual Object* Clone() = 0;

	virtual void Initialize() {}

	const Name& GetName() { return m_name; }

protected:
	Name m_name;
};