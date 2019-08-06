#pragma once
#include "component.h"

class ControllerComponent : public Component
{
public:
	ControllerComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

	void Update() override;
};
