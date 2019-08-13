#include "controller_component.h"
#include "physics_component.h"
#include "player_component.h"
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

	if (keyboardState[SDL_SCANCODE_A]) torque -= 20.0f;
	if (keyboardState[SDL_SCANCODE_D]) torque += 20.0f;
	if (keyboardState[SDL_SCANCODE_W]) force.y += 600.0f;
	if (keyboardState[SDL_SCANCODE_S]) force.y -= 600.0f;

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();

	vector2 rforce = vector2::rotate(force, m_owner->m_transform.rotation);

	component->AddForce(rforce, PhysicsComponent::eForceType::FORCE);
	component->AddTorque(torque, PhysicsComponent::eForceType::FORCE);

	if (keyboardState[SDL_SCANCODE_SPACE]) {
		PlayerComponent* player_component = m_owner->GetComponent<PlayerComponent>();
		player_component->Event("fire_weapon");
	}
}
