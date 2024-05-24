#pragma once
#include "StringPool.h"

class ImmutableString
{
private:
	const char* data;
	unsigned length;

	static StringPool pool;

	void copyFrom(const ImmutableString& other);
	void free();
public:
	ImmutableString();
	ImmutableString(const char* str);
	ImmutableString(const ImmutableString& other);
	ImmutableString& operator=(const ImmutableString& other) = delete;
	~ImmutableString();

	unsigned getLength() const;

	char operator[](size_t index) const;
	const char* c_str() const;
};

std::ostream& operator<<(std::ostream& os, const ImmutableString& str);

bool operator<(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);