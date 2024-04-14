#include <iostream>
#include "BigNumber.h"
#include <cstring>

BigNumber::BigNumber()
{
	MyString number("0");
	this->stringRepresentation = number;
}

const char* BigNumber::getStringRepresentation() const
{
	return stringRepresentation.c_str();
}

void BigNumber::setStringRepresentation(const MyString& str)
{
	stringRepresentation = str;
}

bool BigNumber::operator==(const BigNumber& other) const
{
	return this->stringRepresentation == other.stringRepresentation;
}

bool BigNumber::operator!=(const BigNumber& other) const
{
	return this->stringRepresentation != other.stringRepresentation;;
}

bool BigNumber::operator<(const BigNumber& other) const
{
	return strcmp(this->stringRepresentation.c_str(), other.stringRepresentation.c_str());
}

bool BigNumber::operator>(const BigNumber& other) const
{
	return strcmp(other.stringRepresentation.c_str(), this->stringRepresentation.c_str());
}

BigNumber::BigNumber(const char* inputNumber)
{
	// TODO: validate that input is number
	MyString number(inputNumber);
	this->stringRepresentation = number;
}

BigNumber::BigNumber(long long int inputNumber)
{
	MyString number(inputNumber);
	this->stringRepresentation = number;
}

unsigned getSize(long long int number)
{
	unsigned size = 0;

	if (number == 0)
	{
		return 1;
	}

	while (number != 0)
	{
		size++;
		number /= 10;
	}

	return size;
}

std::istream& operator>>(std::istream& is, BigNumber& number)
{
	MyString str;
	is >> str;
	number.setStringRepresentation(str);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BigNumber& number)
{
	os << number.getStringRepresentation();
	return os;
}