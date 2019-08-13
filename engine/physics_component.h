#pragma once
#include "component.h"

class PhysicsComponent : public Component
{
public:
	enum eForceType {
		FORCE,
		VELOCITY,
		IMPULSE
	};

public:
	PhysicsComponent() : m_max_velocity(0.0f), m_drag(0.0f), m_angular_drag(0.0f) {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	PhysicsComponent* Clone() override { return new PhysicsComponent(*this); }

	void Update() override;

	void AddForce(const vector2& force, eForceType type);
	void AddTorque(float torque, eForceType type);

protected:
	float m_max_velocity;
	float m_drag;
	float m_max_angular_velocity;
	float m_angular_drag;

	vector2 m_force = vector2::zero;
	vector2 m_velocity = vector2::zero;

	float m_torque = 0.0f;
	float m_angular_velocity = 0.0f;

	eForceType m_force_type;
};
