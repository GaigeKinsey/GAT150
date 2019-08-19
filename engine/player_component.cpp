#include "player_component.h"
#include "scene.h"
#include "entity.h"
#include "engine.h"
#include "..\\core\timer.h"

#include <iostream>

void PlayerComponent::Initialize()
{
	m_owner->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Subscribe("score",
		std::bind(&PlayerComponent::OnScore, this, std::placeholders::_1));
}

void PlayerComponent::Destroy()
{
}

bool PlayerComponent::Load(const rapidjson::Value& value)
{
	json::get_float(value, "fire_rate", m_fire_rate);

	return true;
}

void PlayerComponent::Update()
{
	m_fire_timer -= g_timer.dt();
}

void PlayerComponent::FireEvent(const Name& event)
{
	if (event == "fire_weapon" && m_fire_timer <= 0.0f) {
		m_fire_timer = m_fire_rate;

		Entity* entity = m_owner->GetScene()->GetObjectFactory()->Create<Entity>("laser");
		entity->m_transform.translation = m_owner->m_transform.translation;
		entity->m_transform.rotation = m_owner->m_transform.rotation;
		m_owner->GetScene()->Add(entity);
	}
}

bool PlayerComponent::OnScore(const Event<Entity>& event)
{
	ASSERT(event.data[0].type == Variant::eType::INT);
	m_score += event.data[0].as_int;
	std::cout << m_score << std::endl;

	return true;
}
