#include "texture.h"

Texture::~Texture()
{
	Destroy();
}

bool Texture::Create(const Name& name)
{
	SDL_Surface* surface = SDL_LoadBMP(name.c_str());
	m_texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);

	return true;
}

void Texture::Destroy()
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void Texture::Draw(const vector2& position, float angle, const vector2 & scale, const vector2 & origin)
{
	vector2 size = GetSize();
	size = size * scale;

	vector2 screen_position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(screen_position.x);
	dest.y = static_cast<int>(screen_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	vector2 rotation_point = size * origin;
	SDL_Point point = { static_cast<int>(rotation_point.x), static_cast<int>(rotation_point.y) };

	SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_texture, NULL, &dest, angle, &point, SDL_FLIP_NONE);
}

vector2 Texture::GetSize() const
{
	SDL_Point point;

	SDL_QueryTexture(m_texture, 0, 0, &point.x, &point.y);

	return vector2(point.x, point.y);
}
