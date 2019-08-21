#pragma once
#include "component.h"

class AsteroidComponent : public Component
{
public:
	AsteroidComponent() : m_torque(0.0f) {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	AsteroidComponent* Clone() override { return new AsteroidComponent(*this); }

	void Initialize() override;
	void Update() override;

	bool OnCollision(const Event<Entity>& event);

protected:
	bool m_initialized = false;
	vector2 m_force;
	float m_torque;

	vector2 m_force_range;
	vector2 m_torque_range;

	Handle m_collision_event;
};

