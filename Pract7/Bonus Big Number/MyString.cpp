#pragma warning (disable: 4996)
#include "MyString.h"
#include <cstring>
#include <cmath>

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity + 1];
	strcpy(data, other.data);
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void MyString::resize()
{
	unsigned newCap = (capacity + 1) * 2;
	char* newData = new char[newCap];
	capacity = newCap - 1;

	strcpy(newData, data);
	delete[] data;
	data = newData;
}

MyString::MyString(unsigned cap)
{
	size = 0;
	capacity = cap;
	data = new char[capacity + 1];
}

MyString::MyString() : MyString("") {}

MyString::MyString(long long int number)
{
	const char* str = longIntToCharArray(number);

	if (str == nullptr)
	{
		size = 0;
		capacity = 15;
		data = new char[capacity + 1];
		strcpy(data, "");
		return;
	}

	size = strlen(str);
	capacity = std::max((int)nextPowerOfTwo(size), 16) - 1;
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const char* str)
{
	if (str == nullptr)
	{
		size = 0;
		capacity = 15;
		data = new char[capacity + 1];
		strcpy(data, "");
		return;
	}

	size = strlen(str);
	capacity = std::max((int)nextPowerOfTwo(size), 16) - 1;
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

unsigned MyString::length() const
{
	return size;
}

const char* MyString::c_str() const
{
	return data;
}

MyString& MyString::concat(const MyString& other)
{
	if (size + other.size <= capacity)
	{
		size += other.size;
		strcat(data, other.data);
		return *this;
	}

	size += other.size;
	capacity = nextPowerOfTwo(size) - 1;
	char* buff = new char[capacity + 1];
	strcpy(buff, data);
	strcat(buff, other.data);

	delete[] data;
	data = buff;
	return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
	return concat(other);
}

MyString& MyString::operator+=(char ch)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = ch;
	data[size] = '\0';
	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	return std::strcmp(this->data, other.data) == 0 ? true : false;
}

bool MyString::operator!=(const MyString& other) const
{
	return !(this->data == other.data);
}

char& MyString::operator[](unsigned ind)
{
	return data[ind];
}

char MyString::operator[](unsigned ind) const
{
	return data[ind];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	unsigned size = lhs.size + rhs.size;
	unsigned capacity = nextPowerOfTwo(size) - 1;

	MyString res(capacity);
	strcpy(res.data, lhs.data);
	strcat(res.data, rhs.data);

	return res;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	delete[] str.data;
	str.size = strlen(buff);
	str.capacity = std::max((int)nextPowerOfTwo(str.size), 16) - 1;
	str.data = new char[str.capacity + 1];
	strcpy(str.data, buff);

	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.c_str();
	return os;
}

unsigned nextPowerOfTwo(unsigned n)
{
	unsigned step = 1;

	while ((n >> step) > 0) {
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}

const char* longIntToCharArray(long long int number)
{
	// Maximum number of digits in a signed int is 10
	const int bufferSize = 12; // 10 digits + sign + null terminator
	char buffer[bufferSize];
	int index = 0;

	// Handle negative numbers
	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number = -number; // Make number positive
	}

	// Handle the case of zero
	if (number == 0)
	{
		buffer[index++] = '0';
	}

	// Extract digits from the number
	while (number > 0)
	{
		buffer[index++] = '0' + (number % 10);
		number /= 10;
	}

	// Add sign if necessary
	if (isNegative)
	{
		buffer[index++] = '-';
	}

	// Add null terminator
	buffer[index] = '\0';

	// Reverse the string
	std::reverse(buffer, buffer + index);

	// Allocate memory for the result and copy the buffer
	char* result = new char[index + 1];
	strcpy(result, buffer);

	return result;
}
