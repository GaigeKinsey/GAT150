#include "physics_component.h"

void PhysicsComponent::Destroy()
{
}

bool PhysicsComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "max_velocity", m_max_velocity);
	json::get_float(value, "drag", m_drag);
	json::get_float(value, "angular_drag", m_angular_drag);

	return true;
}

void PhysicsComponent::Update()
{
	m_owner->m_transform.translation += m_velocity;
	m_owner->m_transform.rotation += m_angular_velocity;
	m_velocity = m_velocity * m_drag;
	m_angular_velocity = m_angular_velocity * m_angular_drag;
}

void PhysicsComponent::AddForce(const vector2& force, bool relative)
{
	vector2 new_force = (relative) ? vector2::rotate(force, m_owner->m_transform.rotation * math::DEG_TO_RAD) : force;
	m_velocity = m_velocity + new_force;
	if (m_velocity.length() > m_max_velocity) {
		m_velocity = m_velocity.normalized() * m_max_velocity * g_timer.dt();
	}
}

void PhysicsComponent::AddTorque(float torque)
{
	m_angular_velocity = m_angular_velocity + torque;
}
