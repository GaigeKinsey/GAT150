#include "string.h"
#include <string>
#include <sstream>

void string_to_lower(const char* source, char* destination, size_t size)
{
	strcpy_s(destination, size, source);
	for (size_t i = 0; i < strlen(destination); i++) {
		destination[i] = std::tolower(destination[i]);
	}
}

void tokenize(const std::string string, const char delimeter, std::vector<std::string>& strings)
{
	std::stringstream stream(string);
	std::string s;

	while (std::getline(stream, s, delimeter)) {
		strings.push_back(s);
	}
}
