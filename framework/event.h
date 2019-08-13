#pragma once
#include "..\\core\\\name.h"

template <typename T>
struct Event {
	Name name;
	T* sender;
	T* receiver;
};