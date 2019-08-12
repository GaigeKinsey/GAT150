#include "weapon_component.h"
#include "physics_component.h"
#include "scene.h"
#include "engine.h"
#include "..\\core\timer.h"

void WeaponComponent::Destroy()
{
}

bool WeaponComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "force", m_force);
	json::get_float(value, "rate", m_rate);
	json::get_float(value, "lifetime", m_lifetime);

	return true;
}

void WeaponComponent::Update()
{
	if (!m_initialized) {
		//m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->AddSound("", "");
		//m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->PlaySounds("");
	}
	m_lifetime -= g_timer.dt();
	if (m_lifetime <= 0.0f) {
		m_owner->m_destroy = true;
	}

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component) {
		component->AddForce(vector2(0.0f, m_force));
	}
}
