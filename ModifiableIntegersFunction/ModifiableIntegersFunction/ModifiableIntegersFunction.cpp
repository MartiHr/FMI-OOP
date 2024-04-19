#pragma once
#include <iostream>
#include <exception>
#include "ModifiableIntegersFunction.h"
#include "GlobalConstants.h"

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	function = other.function;
	valueByPoint = new KeyValue[constants::INTERVAL_SIZE];

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		int currentIndex = i + INT16_MIN;

		// possibli on one line
		//valueByPoint[i] = other.valueByPoint[i];

		valueByPoint[i].key = other.valueByPoint[i].key;
		valueByPoint[i].value = other.valueByPoint[i].value;
		valueByPoint[i].isExcluded = other.valueByPoint[i].isExcluded;
	}
}

void ModifiableIntegersFunction::free()
{
	function = nullptr;
	delete[] valueByPoint;
}

ModifiableIntegersFunction::ModifiableIntegersFunction()
{
	function = nullptr;
	valueByPoint = new KeyValue[constants::INTERVAL_SIZE];
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*pred)(int16_t number)) : function(pred)
{
	valueByPoint = new KeyValue[constants::INTERVAL_SIZE];

	for (int i = 0; i < constants::INTERVAL_SIZE; ++i)
	{
		valueByPoint[i].key= i + INT16_MIN;
		valueByPoint[i].value = function(i);
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

void ModifiableIntegersFunction::setCustomResult(int16_t input, int16_t result)
{
	//valueByPoint[input].hasCustomValue = true; 
	valueByPoint[input].value = result;
}

void ModifiableIntegersFunction::excludePoint(int16_t point)
{
	valueByPoint[point].isExcluded = true; // Map input to array index
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const
{
	bool isExcluded = valueByPoint[input].isExcluded;

	if (isExcluded)
	{
		throw std::invalid_argument("This point is excluded");
	}

	return valueByPoint[input].value;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
    for (int i = 0; i < constants::INTERVAL_SIZE; i++)
    {
		if (other.valueByPoint[i].isExcluded)
		{
			valueByPoint[i].isExcluded = true;
			continue;
		}

        valueByPoint[i].value += other.valueByPoint[i].value;
    }

    return *this; // Return by reference to the modified object
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
    for (int i = 0; i < constants::INTERVAL_SIZE; i++)
    {
		if (other.valueByPoint[i].isExcluded)
		{
			valueByPoint[i].isExcluded = true;
			continue;
		}

        valueByPoint[i].value -= other.valueByPoint[i].value; // Perform subtraction
    }

    return *this; // Return by reference to the modified object
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator()(const ModifiableIntegersFunction& inner)
{
	ModifiableIntegersFunction result(*this);

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		//int index = i + INT16_MIN;

		if (inner.valueByPoint[i].isExcluded)
		{
			result.valueByPoint[i].isExcluded = true;
			continue;
		}

		int16_t innerRes = inner.valueByPoint[i].value;
		int16_t setIndex = innerRes;
		result.valueByPoint[i].value = this->valueByPoint[innerRes].value;
	}
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return false;
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
    ModifiableIntegersFunction result(lhs);
    result += rhs; // Use the compound assignment operator to perform addition

    return result;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
    ModifiableIntegersFunction result(lhs);
    result -= rhs; // Use the compound assignment operator to perform subtraction

    return result;
}