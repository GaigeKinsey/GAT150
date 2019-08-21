#include "emitter_component.h"
#include "entity.h"
#include "scene.h"
#include "engine.h"
#include "..\\renderer\particle_system.h"


void EmitterComponent::Destroy()
{
}

void EmitterComponent::Update()
{
	m_spawn_timer = m_spawn_timer + g_timer.dt();
	while (m_spawn_timer >= m_spawn_rate)
	{
		m_spawn_timer = m_spawn_timer - m_spawn_rate;

		float lifetime = g_random(m_lifetime_range[0], m_lifetime_range[1]);
		float velocity = g_random(m_velocity_range[0], m_velocity_range[1]);
		float angle = g_random(m_angle_range[0], m_angle_range[1]);

		vector2 random_direction = vector2::rotate(vector2::up, m_owner->m_transform.rotation + (angle * math::DEG_TO_RAD));
		vector2 v = random_direction * velocity;

		m_owner->GetScene()->GetEngine()->GetSystem<ParticleSystem>()->Create(m_texture_name, m_owner->m_transform.translation, v, m_scale, m_damping, lifetime);
	}

	m_lifetime = m_lifetime - g_timer.dt();
	if (m_lifetime <= 0.0f)
	{
		m_owner->m_state[Entity::eState::DESTROY] = 1;
	}
}

bool EmitterComponent::Load(const rapidjson::Value& value)
{
	json::get_name(value, "texture_name", m_texture_name);

	json::get_float(value, "lifetime", m_lifetime);
	json::get_float(value, "spawn_rate", m_spawn_rate);

	json::get_vector2(value, "scale", m_scale);
	json::get_vector2(value, "lifetime_range", m_lifetime_range);
	json::get_vector2(value, "velocity_range", m_velocity_range);
	json::get_vector2(value, "angle_range", m_angle_range);
	json::get_float(value, "damping", m_damping);

	return true;
}
