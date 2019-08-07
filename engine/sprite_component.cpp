#include "sprite_component.h"
#include "scene.h"
#include "engine.h"
#include "..\\renderer\texture.h"

bool SpriteComponent::Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin)
{
	m_name = name;
	m_owner = owner;
	m_texture_name = texture_name;
	m_origin = origin;

	return true;
}

void SpriteComponent::Destroy()
{
}

bool SpriteComponent::Load(const rapidjson::Value& value)
{
	json::get_name(value, "texture_name", m_texture_name);
	json::get_vector2(value, "origin", m_origin);

	return true;
}

void SpriteComponent::Update()
{
}

void SpriteComponent::Draw()
{
	Texture* texture = m_owner->GetScene()->GetEngine()->GetTextureManager()->Get(m_texture_name);
	texture->Draw(m_owner->m_transform.translation, m_owner->m_transform.rotation, m_owner->m_transform.scale, m_origin);
}
