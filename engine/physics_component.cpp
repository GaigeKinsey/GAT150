#include "physics_component.h"

void PhysicsComponent::Destroy()
{
}

bool PhysicsComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "max_velocity", m_max_velocity);
	json::get_float(value, "drag", m_drag);
	json::get_float(value, "max_angular_velocity", m_max_angular_velocity);
	json::get_float(value, "angular_drag", m_angular_drag);

	return true;
}

void PhysicsComponent::Update()
{
	m_velocity += m_force * g_timer.dt();
	if (m_velocity.length() > m_max_velocity) {
		m_velocity = m_velocity.normalized() * m_max_velocity;
	}
	m_owner->m_transform.translation += m_velocity * g_timer.dt();
	m_velocity *= pow(m_drag, g_timer.dt());
	if (m_force_type == eForceType::IMPULSE) {
		m_force = vector2::zero;
	}

	m_angular_velocity += m_torque * g_timer.dt();
	m_angular_velocity = math::clamp(m_angular_velocity, -m_max_angular_velocity, m_max_angular_velocity);

	m_owner->m_transform.rotation += m_angular_velocity * g_timer.dt();
	m_angular_velocity *= pow(m_angular_drag, g_timer.dt());
}

void PhysicsComponent::AddForce(const vector2& force, eForceType type)
{
	m_force_type = type;
	switch (m_force_type)
	{
	case PhysicsComponent::FORCE:
		m_force = force;
		break;
	case PhysicsComponent::VELOCITY:
		m_velocity = force;
		m_force = vector2::zero;
		break;
	case PhysicsComponent::IMPULSE:
		m_force = force;
		break;
	default:
		break;
	}
}

void PhysicsComponent::AddTorque(float torque, eForceType type)
{
	switch (type)
	{
	case PhysicsComponent::FORCE:
		m_torque = torque;
		break;
	case PhysicsComponent::VELOCITY:
		m_angular_velocity = torque;
		m_torque = 0.0f;
		break;
	case PhysicsComponent::IMPULSE:
		m_torque = torque;
		break;
	default:
		break;
	}
}
