#pragma once
#include "render_component.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

class TextComponent : public RenderComponent
{
public:
	TextComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	TextComponent* Clone() override { return new TextComponent(*this); }

	void Update() override;
	void Draw() override;

	void SetText(const char* string);

private:
	Name m_font_name;
	Name m_texture_name;
	color m_color;
	vector2 m_origin;

	std::string m_text;
	std::string m_texture_name_base;
};
