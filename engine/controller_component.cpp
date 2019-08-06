#include "controller_component.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

void ControllerComponent::Destroy()
{
}

bool ControllerComponent::Load(const rapidjson::Value& value)
{
	return false;
}

void ControllerComponent::Update()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_A]) m_owner->m_transform.translation.x -= 0.1f;
	if (keyboardState[SDL_SCANCODE_D]) m_owner->m_transform.translation.x += 0.1f;
	if (keyboardState[SDL_SCANCODE_W]) m_owner->m_transform.translation.y -= 0.1f;
	if (keyboardState[SDL_SCANCODE_S]) m_owner->m_transform.translation.y += 0.1f;

	if (keyboardState[SDL_SCANCODE_Q]) m_owner->m_transform.rotation -= 0.1f;
	if (keyboardState[SDL_SCANCODE_E]) m_owner->m_transform.rotation += 0.1f;
}
