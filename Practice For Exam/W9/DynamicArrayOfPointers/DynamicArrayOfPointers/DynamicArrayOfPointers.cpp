#include <iostream>
#include "DynamicArrayOfPointers.h"

void DynamicArrayOfPointers::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;

	size = 0;
	capacity = 0;
}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new A * [capacity];

	for (int i = 0; i < capacity; i++)
	{
		if (other.data[i] == nullptr)
		{
			data[i] = nullptr;
		}
		else
		{
			data[i] = new A(*other.data[i]);
		}
	}
}

void DynamicArrayOfPointers::moveFrom(DynamicArrayOfPointers&& other) noexcept
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

void DynamicArrayOfPointers::resize(size_t newCapacity)
{
	A** newData = new A * [newCapacity];

	for (int i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;

	data = newData;
	capacity = newCapacity;
}

int DynamicArrayOfPointers::getFirstFreeIndex() const
{
	for (int i = 0; i < capacity; i++)
	{
		if (data[i] == nullptr)
		{
			return i;
		}
	}

	return -1;
}

DynamicArrayOfPointers::DynamicArrayOfPointers()
{
	capacity = 8;
	size = 0;
	data = new A * [capacity] {nullptr};
}

DynamicArrayOfPointers::DynamicArrayOfPointers(const DynamicArrayOfPointers& other)
{
	copyFrom(other);
}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator=(const DynamicArrayOfPointers& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicArrayOfPointers::~DynamicArrayOfPointers()
{
	free();
}

DynamicArrayOfPointers::DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept
{
	moveFrom(std::move(other));
}

DynamicArrayOfPointers DynamicArrayOfPointers::operator=(DynamicArrayOfPointers&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(const A& current)
{
	if (size + 1 > capacity)
	{
		resize(capacity * 2);
	}

	int freeIndex = getFirstFreeIndex();

	if (freeIndex == -1)
	{
		return;
	}

	data[freeIndex] = new A(current);
	size++;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(A&& obj)
{
	if (size + 1 > capacity)
	{
		resize(capacity * 2);
	}

	int freeIndex = getFirstFreeIndex();

	if (freeIndex == -1)
	{
		return;
	}

	data[freeIndex] = new A(std::move(obj));
	size++;
}

bool DynamicArrayOfPointers::containsAt(unsigned index) const
{
	if (index >= capacity)
	{
		return false;
	}

	return data[index] == nullptr;
}

void DynamicArrayOfPointers::popBack()
{
	if (size < 0)
	{
		return;
	}

	delete data[size - 1];
	size--;
}

void DynamicArrayOfPointers::removeAt(size_t index)
{
	if (index + 1 > capacity)
	{
		return;
	}

	delete data[index];
	data[index] = nullptr;
	size--;
}

void DynamicArrayOfPointers::setAtIndex(const A& obj, size_t index)
{
	if (data[index] != nullptr)
	{
		data[index]->operator=(obj);
	}
	else
	{
		data[index] = new A(obj);
		size++;
	}
}

void DynamicArrayOfPointers::setAtIndex(A&& obj, size_t index)
{
	if (index + 1 > capacity)
	{
		return;
	}

	if (data[index] != nullptr)
	{
		*data[index] = obj;
	}
	else
	{
		data[index] = new A(std::move(obj));
		size++;
	}
}

