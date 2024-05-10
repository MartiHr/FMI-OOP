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