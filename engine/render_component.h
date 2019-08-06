#pragma once
#include "component.h"

class RenderComponent : public Component
{
public:
	RenderComponent() : Component() {}

	virtual void Draw() = 0;
};
