#pragma once
#include "component.h"

class PlayerComponent : public Component
{
public:
	PlayerComponent() : m_fire_rate(0.0f), m_fire_timer(0.0f) {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new PlayerComponent(*this); }

	void Update() override;

	void Event(const Name& event);

protected:
	float m_fire_rate;
	float m_fire_timer = 0.0f;
};

