#include "name.h"
#include "assert.h"
#include "string.h"

char* Name::ms_names = nullptr;

Name::Name(const char* string)
{
	ASSERT_MSG(strlen(string) < MAX_NAME_SIZE, "name size is greater than max name size.");

	char lower_string[MAX_NAME_SIZE];
	string_to_lower(string, lower_string, MAX_NAME_SIZE);

	m_id = static_cast<u32>(std::hash<std::string>{}(lower_string));
	m_index = m_id % MAX_ENTRIES;
	strcpy_s(ms_names + (m_index * MAX_NAME_SIZE), MAX_NAME_SIZE, string);
}

bool Name::operator==(const Name& other) const
{
	return (m_id == other.m_id);
}

bool Name::operator!=(const Name& other) const
{
	return (m_id != other.m_id);
}

bool Name::operator<(const Name& other) const
{
	return (m_id < other.m_id);
}

std::string Name::ToString() const
{
	return std::string(c_str());
}

const char* Name::c_str() const
{
	return ms_names + (m_index * MAX_NAME_SIZE);
}

void Name::AllocNames()
{
	ms_names = new char[MAX_ENTRIES * MAX_NAME_SIZE];
}

void Name::FreeNames()
{
	delete ms_names;
}
