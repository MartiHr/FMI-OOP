#include "StringPool.h"
#include <iostream>

int StringPool::findString(const char* soghtString) const
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(records[i].str, soghtString) == 0)
		{
			return i;
		}
	}

	return -1;
}

int StringPool::allocateString(const char* str)
{
	if (size + 1 > capacity)
	{
		resize();
	}

	int placeIndex = size + 1;
	records[placeIndex].str = new char[strlen(str) + 1];
	strcpy(records[placeIndex].str, str);
	records[placeIndex].refCount = 1;

	return placeIndex;
}

void StringPool::deleteRecord(int index)
{
	// no empty spaces allowed
	std::swap(records[index], records[size - 1]);

	delete[] records[size - 1].str;
	records[size - 1].str = nullptr;
	records[index].refCount = 0;

	size--;
}

void StringPool::resize()
{
	StringRecord* newRecords = new StringRecord[capacity * 2];

	for (int i = 0; i < size; i++)
	{
		newRecords[i] = records[i];
	}

	delete[] records;
	records = newRecords;
}

StringPool::StringPool()
{
	size = 0;
	capacity = 8;
	records = new StringRecord[capacity];
}

StringPool::~StringPool()
{
	for (int i = 0; i < capacity; i++)
	{
		records[i].refCount = 0;
		delete records[i].str;
	}

	delete[] records;
	records = nullptr;
	size = 0;
	capacity = 0;
}

const char* StringPool::getString(const char* str)
{
	int strIndex = findString(str);

	if (strIndex != -1)
	{
		records[strIndex].refCount++;

		return records[strIndex].str;
	}
	else
	{
		allocateString(str);

		return records[strIndex].str;
	}
}

void StringPool::removeOneString(const char* str)
{
	int strIndex = findString(str);

	if (strIndex == -1)
	{
		throw std::logic_error("No such string");
	}

	records[strIndex].refCount--;

	if (records[strIndex].refCount == 0)
	{
		deleteRecord(strIndex);
	}
}

void StringPool::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "We have: " << records[i].str << " " << records[i].refCount << " times" << std::endl;
	}

	std::cout << std::endl;
}
