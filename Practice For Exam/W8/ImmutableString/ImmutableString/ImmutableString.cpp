#include "ImmutableString.h"
#include <iostream>

void ImmutableString::copyFrom(const ImmutableString& other)
{
	data = pool.getString(other.data);
}

void ImmutableString::free()
{
	pool.removeOneString(data);
	data = nullptr;
}

ImmutableString::ImmutableString() : ImmutableString("") {}

ImmutableString::ImmutableString(const char* str)
{
	data = pool.getString(str);
	length = strlen(data);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
	copyFrom(other);
}

ImmutableString::~ImmutableString()
{
	free();
}

unsigned ImmutableString::getLength() const
{
	return length;
}

char ImmutableString::operator[](size_t index) const
{
	return data[index];
}

const char* ImmutableString::c_str() const
{
	return data;
}


std::ostream& operator<<(std::ostream& os, const ImmutableString& str)
{
	return os << str.c_str();
}

bool operator<(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

