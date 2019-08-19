#include "sprite_animation_component.h"
#include "scene.h"
#include "engine.h"
#include "..\\renderer\texture.h"

void SpriteAnimationComponent::Initialize()
{
	m_num_frames = 25;
	m_frames_row = 5;
	m_frames_col = 5;
	m_frame = 0;
	m_frame_timer = 0;
	m_frame_rate = 1.0f / 30.0f;
}

bool SpriteAnimationComponent::Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin)
{
	m_name = name;
	m_owner = owner;
	m_texture_name = texture_name;
	m_origin = origin;

	return true;
}

void SpriteAnimationComponent::Destroy()
{
}

bool SpriteAnimationComponent::Load(const rapidjson::Value& value)
{
	json::get_name(value, "texture_name", m_texture_name);
	json::get_vector2(value, "origin", m_origin);

	return true;
}

void SpriteAnimationComponent::Update()
{
	m_frame_timer += g_timer.dt();
	while (m_frame_timer >= m_frame_rate) {
		m_frame_timer -= m_frame_rate;
		m_frame++;
	}

	Texture* texture = m_owner->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);
	vector2 texture_size = texture->GetSize();
	vector2 frame_num(m_frames_col, m_frames_row);

	vector2 frame_size = texture_size / frame_num;

	m_rect.x = static_cast<int>((m_frame % m_frames_col) * frame_size.x);
	m_rect.y = static_cast<int>((m_frame / m_frames_col) * frame_size.y);

	m_rect.w = static_cast<int>(frame_size.x);
	m_rect.h = static_cast<int>(frame_size.y);
}

void SpriteAnimationComponent::Draw()
{
	Texture* texture = m_owner->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);
	texture->Draw(m_rect, m_owner->m_transform.translation, m_owner->m_transform.rotation * math::RAD_TO_DEG, m_owner->m_transform.scale, m_origin);
}
