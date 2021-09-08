#include <cstring>

#include "protocol.hpp"

void Str31::Set(const char *newText)
{
	std::memset_s(text, 0, 31);
	size = std::strlen(newText);
	std::strncpy(text, newText, size >= 31 ? 31 : size);
}

void Str31::Set(const Str31 &other)
{
	Set(other.text);
}

void Str63::Set(const char *newText)
{
	std::memset_s(text, 0, 63);
	size = std::strlen(newText);
	std::strncpy(text, newText, size >= 63 ? 63 : size);
}

void Str63::Set(const Str63 &other)
{
	Set(other.text);
}
