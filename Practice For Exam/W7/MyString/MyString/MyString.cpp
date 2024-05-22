#include "MyString.h"

namespace StringHelperFunctions 
{
	unsigned int getNextPowerOfTwo(unsigned int n) 
	{
		unsigned int step = 1;

		while ((n >> step) > 0) 
		{
			n |= n >> step;
			step *= 2;
		}

		return n + 1;
	}
}

using namespace StringHelperFunctions;

MyString::MyString() :MyString("") { }

MyString::MyString(const char* str)
{
	if (!str)
	{
		data = new char[capacity + 1];
		data[0] = '\0';
	}
	else
	{
		length = strlen(str);
		capacity = std::max((int)getNextPowerOfTwo(length), 16) - 1;
		data = new char[capacity + 1];
		strcpy(data, str);
	}
}

