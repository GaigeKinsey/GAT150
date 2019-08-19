#pragma once

#include "renderer.h"
#include "..\\math\vector2.h"
#include "..\\renderer\font.h"
#include "..\\resources\resource.h"

class Texture : public Resource
{
public:
	Texture(Renderer* renderer) : m_renderer(renderer), m_texture(nullptr) {}
	~Texture();

	bool Create(const Name& name);
	bool CreateFromFont(Font* font, const char* string, const color& font_color);
	void Destroy();

	void Draw(SDL_Rect& rect, const vector2& position, float angle = 0.0f, const vector2 & scale = vector2::one, const vector2& origin = vector2::zero);
	void Draw(const vector2& position, float angle = 0.0f, const vector2 & scale = vector2::one, const vector2& origin = vector2::zero);
	vector2 GetSize() const;

protected:
	SDL_Texture* m_texture;
	Renderer* m_renderer;
};