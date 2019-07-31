#include "texture.h"

Texture::~Texture()
{
	Destroy();
}

bool Texture::Create(const std::string& name)
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

void Texture::Draw(const vector2& position, const vector2& origin, const vector2& scale, float angle)
{
	SDL_Rect dest = { position.x, position.y, 0, 0 };
	SDL_Point point;
	SDL_QueryTexture(m_texture, 0, 0, &point.x, &point.y);
	dest.w = point.x;
	dest.h = point.y;

	SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_texture, NULL, &dest, angle, 0, SDL_FLIP_NONE);
}

vector2 Texture::GetSize() const
{
	SDL_Point point;

	SDL_QueryTexture(m_texture, 0, 0, &point.x, &point.y);

	return vector2(point.x, point.y);
}
