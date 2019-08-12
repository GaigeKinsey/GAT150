#pragma once
#include "component.h"

class WeaponComponent : public Component
{
public:
	WeaponComponent() : m_force(0.0f), m_rate(0.0f), m_lifetime(0.0f) {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new WeaponComponent(*this); }

	void Update() override;

protected:
	bool m_initialized = false;

	float m_force;
	float m_rate;

	float m_lifetime;
};

