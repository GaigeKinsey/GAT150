#pragma once
#include "render_component.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

class SpriteAnimationComponent : public RenderComponent
{
public:
	SpriteAnimationComponent() : m_frame(0), m_frame_rate(0.0f), m_frame_timer(0.0f), m_frames_col(0), m_frames_row(0), m_num_frames(0), m_rect(SDL_Rect()) {}

	void Initialize() override;
	bool Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin = vector2::zero);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	SpriteAnimationComponent* Clone() override { return new SpriteAnimationComponent(*this); }

	void Update() override;
	void Draw() override;

private:
	Name m_texture_name;
	vector2 m_origin;
	SDL_Rect m_rect;

	int m_num_frames;
	int m_frames_row;
	int m_frames_col;

	int m_frame;
	float m_frame_timer;
	float m_frame_rate;
};
