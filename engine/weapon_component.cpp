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

void WeaponComponent::Initialize()
{
	m_owner->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Subscribe("collision",
		std::bind(&WeaponComponent::OnCollision, this, std::placeholders::_1));
}

void WeaponComponent::Update()
{
	m_lifetime -= g_timer.dt();
	if (m_lifetime <= 0.0f) {
		m_owner->m_destroy = true;
	}

	if (!m_initialized) {
		m_initialized = true;
		m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->AddSound("laser", "audio/laser.wav");
		m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->PlaySounds("laser");

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component) {
			vector2 force = vector2::rotate(vector2(0.0f, m_force), m_owner->m_transform.rotation);
			component->AddForce(force, PhysicsComponent::eForceType::VELOCITY);
		}
	}
}

bool WeaponComponent::OnCollision(const Event<Entity>& event)
{
	if ((m_owner == event.sender && event.receiver->GetName() == "asteroid") || (m_owner == event.receiver && event.sender->GetName() == "asteroid")) {
		m_owner->m_destroy = true;
	}

	return true;
}
