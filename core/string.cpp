#include "string.h"
#include <string>

void string_to_lower(const char* source, char* destination, size_t size)
{
	strcpy_s(destination, size, source);
	for (size_t i = 0; i < strlen(destination); i++) {
		destination[i] = std::tolower(destination[i]);
	}
}
