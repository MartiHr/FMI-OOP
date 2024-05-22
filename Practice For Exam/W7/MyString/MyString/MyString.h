#pragma once
#include <iostream>

namespace StringHelperFunctions
{
	unsigned int getNextPowerOfTwo(unsigned int n);
}

class MyString
{
private:
	char* data = nullptr;
	size_t length = 0;
	size_t capacity = 15;

	void resize(size_t lengthToFit);

	explicit MyString(size_t capacity);

	void free();
	void copyFrom(const MyString& other);
public:
	MyString();
	MyString(const char* str);

};