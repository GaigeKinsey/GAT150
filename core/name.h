#pragma once

#include "types.h"
#include <string>

class Name
{
public:
	Name(const char* string);

	bool operator == (const Name& other);
	bool operator != (const Name& other);

	std::string ToString() const;
	const char* c_str() const;

	u32 GetID() const { return m_id; }

private:
	u32 m_id;
	u32 m_index;

	static const u32 MAX_ENTRIES = 65536;
	static const u32 MAX_NAME_SIZE = 64;
	using entries = char[MAX_ENTRIES][MAX_NAME_SIZE]; // (2^16 * 64) = 4,194,304
	
	static entries ms_names;
};

