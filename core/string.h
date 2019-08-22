#pragma once
#include "core.h"

void string_to_lower(const char* source, char* destination, size_t size);
void tokenize(const std::string string, const char delimeter, std::vector<std::string>& strings);