#pragma once
#include "component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() : m_max_velocity(0.0f), m_drag(0.0f), m_angular_drag(0.0f) {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	void Update() override;

	void AddForce(const vector2& force, bool relative = true);
	void AddTorque(float torque);

protected:
	float m_max_velocity;
	float m_drag;
	float m_angular_drag;

	vector2 m_velocity = vector2::zero;
	float m_angular_velocity = 0.0f;
};
