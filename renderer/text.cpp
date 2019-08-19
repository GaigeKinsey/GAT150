#include "text.h"

Text::~Text()
{
	Destroy();
}

bool Text::Create(const Name& name)
{
	m_font = TTF_OpenFont(name.c_str(), 32);

	return true;
}

bool Text::CreateFromFont(Font* font, const char* string, const color& font_color)
{
	SDL_Color c;
	c.r = static_cast<Uint8>(font_color.r * 255.0f);
	c.g = static_cast<Uint8>(font_color.g * 255.0f);
	c.b = static_cast<Uint8>(font_color.b * 255.0f);

	SDL_Surface* surface = TTF_RenderText_Solid(m_font, string, c);
	ASSERT(surface);
	m_texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);

	return m_texture != nullptr;
}

void Text::Destroy()
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
	if (m_font) {
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
}

void Text::Draw(const vector2& position, float angle, const vector2& scale, const vector2& origin)
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

vector2 Text::GetSize() const
{
	SDL_Point point;

	SDL_QueryTexture(m_texture, 0, 0, &point.x, &point.y);

	return vector2(point.x, point.y);
}

void Text::SetText(const char* string)
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}

	SDL_Color c;
	c.r = static_cast<Uint8>(m_color.r * 255.0f);
	c.g = static_cast<Uint8>(m_color.g * 255.0f);
	c.b = static_cast<Uint8>(m_color.b * 255.0f);

	SDL_Surface* surface = TTF_RenderText_Solid(m_font, string, c);
	m_texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);
}
