#pragma once
#include <iostream>
#include "MyString.h"

class BigNumber
{
private:
	MyString stringRepresentation;
public:
	BigNumber();
	// Add validation
	BigNumber(const char* number);
	BigNumber(long long int number);

	const char* getStringRepresentation() const;

	void setStringRepresentation(const MyString& str);

	bool operator == (const BigNumber& other) const;
	bool operator != (const BigNumber& other) const;
	bool operator < (const BigNumber& other) const;
	bool operator > (const BigNumber& other) const;

	BigNumber& operator += (const BigNumber& other);
	BigNumber operator + (const BigNumber& other) const;
	BigNumber& operator -= (const BigNumber& other);
	BigNumber operator - (const BigNumber& other) const;
	BigNumber& operator *= (const BigNumber& other);
	BigNumber operator * (const BigNumber& other) const;

	BigNumber& operator ++ ();
	BigNumber operator ++ (int);

	BigNumber& operator -- ();
	BigNumber operator -- (int);

	BigNumber& operator - ();

	BigNumber& operator /= (const BigNumber& other);
	BigNumber operator / (const BigNumber& other) const;
	BigNumber& operator %= (const BigNumber& other);
	BigNumber operator % (const BigNumber& other) const;

	friend std::istream& operator>>(std::istream& is, BigNumber& lhs);
};

std::ostream& operator<<(std::ostream&, const BigNumber& lhs);
