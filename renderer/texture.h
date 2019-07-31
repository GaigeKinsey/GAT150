#pragma once

#include "renderer.h"
#include "..\\math\vector2.h"

class Texture
{
public:
	Texture(Renderer* renderer) : m_renderer(renderer) {}
	~Texture();

	bool Create(const std::string& name);
	void Destroy();

	void Draw(const vector2& position, const vector2& origin = vector2::zero, const vector2& scale = vector2::one, float angle = 0);
	vector2 GetSize() const;

protected:
	SDL_Texture* m_texture;
	Renderer* m_renderer;
};