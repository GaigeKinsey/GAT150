#include "asteroid_component.h"
#include "..\\core\random.h"
#include "physics_component.h"

void AsteroidComponent::Destroy()
{
}

bool AsteroidComponent::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "force_range", m_force_range);
	json::get_vector2(value, "torque_range", m_torque_range);

	return true;
}

void AsteroidComponent::Update()
{
	if (!m_initialized) {
		m_initialized = true;

		float force = g_random(m_force_range[0], m_force_range[1]);
		m_force = vector2::rotate(vector2(0.0f, force), g_random(0.0f, math::TWO_PI));
		m_torque = g_random(m_torque_range[0], m_torque_range[1]);

		PhysicsComponent * component = m_owner->GetComponent<PhysicsComponent>();
		if (component) {
			component->AddForce(m_force, false);
			component->AddTorque(m_torque * math::DEG_TO_RAD);
		}
	}
}
