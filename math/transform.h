#pragma once

#include "..\\core\core.h"
#include "matrix33.h"

struct transform {
	vector2 translation;
	float rotation;
	float speed;
	vector2 scale;

	matrix33 mxWorld;

	transform() : rotation(0.0f), speed(0.0f) {}
	transform(vector2& translation, float rotation, float speed, vector2 scale) :
		translation(translation),
		rotation(rotation),
		speed(speed),
		scale(scale) {}

	bool Load(const rapidjson::Value& value);
	void update();
};