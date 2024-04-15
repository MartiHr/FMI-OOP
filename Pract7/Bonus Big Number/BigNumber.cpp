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

BigNumber& BigNumber::operator*=(const BigNumber& other)
{
	return *this;
}

BigNumber BigNumber::operator*(const BigNumber& other) const
{
	int len1 = this->stringRepresentation.length();
	int len2 = other.stringRepresentation.length();
	int len3 = len1 + len2; // maximum length of result

	int* result = new int[len3](); // initialize result array with 0

	// Multiply each digit and store the result in the result array
	for (int i = len1 - 1; i >= 0; i--) {
		for (int j = len2 - 1; j >= 0; j--) {
			int mul = (this->getStringRepresentation()[i] - '0') * (other.getStringRepresentation()[j] - '0');
			int sum = mul + result[i + j + 1]; // add to the current digit
			result[i + j] += sum / 10; // carry over
			result[i + j + 1] = sum % 10; // store the digit
		}
	}

	// Convert the result array to character array
	char* result_char = new char[len3 + 1];
	int idx = 0;
	while (idx < len3 && result[idx] == 0) idx++; // skip leading zeros
	for (int i = idx; i < len3; i++) {
		result_char[i - idx] = result[i] + '0';
	}
	result_char[len3 - idx] = '\0'; // null-terminate the string

	delete[] result; // free the memory

	return result_char;
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