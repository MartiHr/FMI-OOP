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
		allocateString(const char* str);
	}
}
