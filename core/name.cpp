#include "name.h"
#include "assert.h"
#include "string.h"

Name::entries Name::ms_names;

Name::Name(const char* string)
{
	ASSERT_MSG(strlen(string) < MAX_NAME_SIZE, "name size is greater than max name size.");

	char lower_string[MAX_NAME_SIZE];
	string_to_lower(string, lower_string, MAX_NAME_SIZE);

	m_id = static_cast<u32>(std::hash<std::string>{}(lower_string));
	m_index = m_id % MAX_ENTRIES;
	strcpy_s(ms_names[m_index], MAX_NAME_SIZE, string);
}

bool Name::operator==(const Name& other)
{
	return (m_id == other.m_id);
}

bool Name::operator!=(const Name& other)
{
	return (m_id != other.m_id);
}

std::string Name::ToString() const
{
	return std::string(ms_names[m_index]);
}

const char* Name::c_str() const
{
	return ms_names[m_index];
}
