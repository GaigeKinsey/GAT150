#pragma once
#include "component.h"

class AsteroidComponent : public Component
{
public:
	AsteroidComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	void Update() override;

protected:
	bool m_initialized = false;
	vector2 m_force;
	float m_torque;

	vector2 m_force_range;
	vector2 m_torque_range;
};

