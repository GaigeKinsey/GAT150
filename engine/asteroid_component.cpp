#include "asteroid_component.h"
#include "physics_component.h"
#include "..\\core\random.h"
#include "engine.h"
#include "entity.h"
#include "scene.h"

void AsteroidComponent::Destroy()
{
}

bool AsteroidComponent::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "force_range", m_force_range);
	json::get_vector2(value, "torque_range", m_torque_range);

	return true;
}

void AsteroidComponent::Initialize()
{
	m_owner->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Subscribe("collision",
		std::bind(&AsteroidComponent::OnCollision, this, std::placeholders::_1));

	float force = g_random(m_force_range[0], m_force_range[1]);
	m_force = vector2::rotate(vector2(0.0f, force), g_random(0.0f, math::TWO_PI));
	m_torque = g_random(m_torque_range[0], m_torque_range[1]);

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component) {
		component->AddForce(m_force, PhysicsComponent::eForceType::VELOCITY);
		component->AddTorque(m_torque * math::DEG_TO_RAD, PhysicsComponent::eForceType::VELOCITY);
	}
}

void AsteroidComponent::Update()
{
	//
}

bool AsteroidComponent::OnCollision(const Event<Entity>& event)
{
	if ((m_owner == event.sender && event.receiver->GetTag() == "player_weapon") || (m_owner == event.receiver && event.sender->GetTag() == "player_weapon")) {
		m_owner->m_destroy = true;

		m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->AddSound("explosion", "audio/explosion.wav");
		m_owner->GetScene()->GetEngine()->GetSystem<AudioSystem>()->PlaySounds("explosion");

		Entity* entity = m_owner->GetScene()->GetObjectFactory()->Create<Entity>("explosion");
		entity->m_transform.translation = m_owner->m_transform.translation;

		m_owner->GetScene()->Add(entity);
	}

	return true;
}
