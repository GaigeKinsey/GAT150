#pragma once

#include "renderer.h"
#include "..\\math\vector2.h"
#include "..\\renderer\font.h"
#include "..\\resources\resource.h"

class Text : public Resource
{
public:
	Text(Renderer* renderer) : m_renderer(renderer), m_texture(nullptr) {}
	~Text();

	bool Create(const Name& name);
	bool CreateFromFont(Font* font, const char* string, const color& font_color);
	void Destroy();

	void Draw(const vector2& position, float angle = 0.0f, const vector2 & scale = vector2::one, const vector2 & origin = vector2::zero);
	vector2 GetSize() const;

	const color GetColor() const { return m_color; }
	void SetColor(color color) {
		m_color = color;
	}
	void SetText(const char* string);

protected:
	SDL_Texture* m_texture;
	Renderer* m_renderer;

	color m_color;
	TTF_Font* m_font = nullptr;
};