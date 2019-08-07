#include "controller_component.h"
#include "physics_component.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

void ControllerComponent::Destroy()
{
}

bool ControllerComponent::Load(const rapidjson::Value& value)
{
	return true;
}

void ControllerComponent::Update()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	vector2 force = vector2::zero;
	float torque = 0.0f;

	if (keyboardState[SDL_SCANCODE_A]) torque -= 1.0f;
	if (keyboardState[SDL_SCANCODE_D]) torque += 1.0f;
	if (keyboardState[SDL_SCANCODE_W]) force.y += 1.0f;
	if (keyboardState[SDL_SCANCODE_S]) force.y -= 1.0f;

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	component->AddForce(force);
	component->AddTorque(torque);
}
