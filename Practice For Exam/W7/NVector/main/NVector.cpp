#include <iostream>
#include "NVector.h"


void NVector::copyFrom(const NVector& other)
{
	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void NVector::free()
{
	delete[] data;
	size = 0;
}

NVector::NVector(size_t size)
{
	this->size = size;
	data = new int[size];
}

NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

NVector::~NVector()
{
	free();
}

NVector& NVector::operator+=(const NVector& other)
{
	if (size != other.size)
	{
		throw std::logic_error("The vectors should have the same size");
	}
	for (size_t i = 0; i < size; i++)
	{
		data[i] += other.data[i];
	}

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (size != other.size)
	{
		throw std::logic_error("The vectors should have the same size");
	}
	for (size_t i = 0; i < size; i++)
	{
		data[i] -= other.data[i];
	}

	return *this;
}

NVector& NVector::operator*=(size_t scalar)
{
	for (int i = 0; i < size; i++)
	{
		data[i] *= scalar;
	}

	return *this;
}

int NVector::operator[](size_t index) const
{
	if (index > size)
	{
		throw std::invalid_argument("Invalid index");
	}

	return data[index];
}

int& NVector::operator[](size_t index) 
{
	if (index > size)
	{
		throw std::invalid_argument("Invalid index");
	}

	return data[index];
}

size_t NVector::getSize() const
{
	return size;
}

//
//bool operator||(const NVector& lhs, const NVector& rhs)
//{
//	if (~lhs != ~rhs) {
//	}
//}
//

std::istream& operator>>(std::istream& is, NVector& vector)
{
	for (int i = 0; i < vector.size; i++)
	{
		is >> vector[i];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const NVector& vector)
{
	os << "[ ";
	
	for (int i = 0; i < vector.getSize(); i++)
	{
		os << vector[i] << " ";
	}

	os << " ]";

	return os;
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
	NVector result(lhs);
	result += rhs;

	return result;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
	NVector result(lhs);
	result -= rhs;

	return result;
}

NVector operator*(const NVector& lhs, size_t scalar)
{
	NVector result(lhs);
	result = result * scalar;

	return result;
}

NVector operator*(size_t scalar, const NVector& rhs)
{
	return rhs * scalar;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
	{
		throw std::invalid_argument("The vectors should have the same size!");
	}

	double ratio = (double)lhs[0] / rhs[0];

	for (int i = 1; i < lhs.getSize(); i++)
	{
		double current = (double)(lhs[i]) / rhs[i];

		double diff = current - ratio;
		// check current different than ratio (compare doubles)
		if (!((diff < 1e-6) && (-diff < 1e-6)))
		{
			return false;
		}

		ratio = current;
	}
}

// scalar product of vectors (dot product)
size_t operator%(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
	{
		throw std::invalid_argument("The vectors should have the same size!");
	}

	size_t res = 0;
	for (int i = 0; i < lhs.getSize(); i++)
	{
		res += lhs[i] * rhs[i];
	}

	return res;
}

bool operator|=(const NVector& lhs, const NVector& rhs)
{
	return  lhs % rhs == 0; //the size check is done by %
}