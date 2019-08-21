#pragma once
#include "component.h"

class EmitterComponent : public Component
{
public:
	EmitterComponent() {}
	virtual ~EmitterComponent() {}

	void Destroy() override;
	virtual bool Load(const rapidjson::Value& value) override;
	virtual EmitterComponent* Clone() { return new EmitterComponent(*this); }

	virtual void Update() override;

protected:
	Name m_texture_name;
	vector2 m_direction;
	vector2 m_scale;
	float m_lifetime;
	float m_spawn_timer = 0.0f;

	float m_spawn_rate;

	vector2 m_lifetime_range;
	vector2 m_velocity_range;
	vector2 m_angle_range;
	float m_damping;
};
