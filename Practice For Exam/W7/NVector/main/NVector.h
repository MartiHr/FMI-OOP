#pragma once
#include <iostream>

class NVector
{
private:
	int* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();
public:

	NVector(size_t size);

	NVector(const NVector& other);
	NVector& operator=(const NVector& other);
	~NVector();

	size_t getSize() const;

	NVector& operator*=(size_t scalar);

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);

	int operator[](size_t index) const; // get
	int& operator[](size_t index); // get set

	friend std::istream& operator>>(std::istream& is, NVector& vector);
	friend std::ostream& operator<<(std::ostream& os, const NVector& vector);
};

//Allow chaining
NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);

NVector operator*(const NVector& lhs, size_t scalar);
NVector operator*(size_t scalar, const NVector& rhs);

// Check whether two vectors ara parallel
bool operator||(const NVector& lhs, const NVector& rhs);

//scalar product
size_t operator%(const NVector& lhs, const NVector& rhs);

//are perpendicular
bool operator|=(const NVector& lhs, const NVector& rhs);