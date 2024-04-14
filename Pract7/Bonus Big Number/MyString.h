#pragma once

#pragma once
#include <iostream>

class MyString
{
private:
	char* data;
	unsigned size;
	unsigned capacity;

	void copyFrom(const MyString& other);
	void free();
	void resize();

	explicit MyString(unsigned cap);
public:
	MyString();
	MyString(long long int number);
	MyString(const char* str);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	unsigned length() const;
	const char* c_str() const; // getData
	MyString& concat(const MyString& other);

	MyString& operator+=(const MyString& other);
	MyString& operator+=(char ch);

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;

	friend MyString operator+(const MyString& lhs, const MyString& rhs);

	char& operator[](unsigned ind);
	char operator[](unsigned ind) const;

	friend std::istream& operator>>(std::istream& is, MyString& lhs);
};

std::ostream& operator<<(std::ostream&, const MyString& lhs);

unsigned nextPowerOfTwo(unsigned n);
const char* longIntToCharArray(long long int number);

