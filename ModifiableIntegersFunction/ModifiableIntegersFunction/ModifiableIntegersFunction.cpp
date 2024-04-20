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

bool ModifiableIntegersFunction::isDefined()
{
	for (size_t i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		if (valueByPoint[i].isExcluded)
		{
			return false;
		}
	}

	return true;
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
		valueByPoint[i].key = i + INT16_MIN;
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
		if (inner.valueByPoint[i].isExcluded)
		{
			result.valueByPoint[i].isExcluded = true;
			continue;
		}

		int16_t innerRes = inner.valueByPoint[i].value;
		int16_t setIndex = innerRes + (-INT16_MIN);
		result.valueByPoint[i].value = this->valueByPoint[setIndex].value;
	}

	return result;
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		int16_t lhsValue = lhs.valueByPoint[i].value;
		int16_t rhsValue = rhs.valueByPoint[i].value;

		if (lhs.valueByPoint[i].isExcluded)
		{
			lhsValue = INT16_MIN;
		}

		if (rhs.valueByPoint[i].isExcluded)
		{
			rhsValue = INT16_MIN;
		}

		if (lhsValue <= rhsValue)
		{
			return false;
		}
	}

	return true;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		int16_t lhsValue = lhs.valueByPoint[i].value;
		int16_t rhsValue = rhs.valueByPoint[i].value;

		if (lhs.valueByPoint[i].isExcluded)
		{
			lhsValue = INT16_MIN;
		}

		if (rhs.valueByPoint[i].isExcluded)
		{
			rhsValue = INT16_MIN;
		}

		if (lhsValue >= rhsValue)
		{
			return false;
		}
	}

	return true;
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		int16_t lhsValue = lhs.valueByPoint[i].value;
		int16_t rhsValue = rhs.valueByPoint[i].value;

		if (lhs.valueByPoint[i].isExcluded)
		{
			lhsValue = INT16_MIN;
		}

		if (rhs.valueByPoint[i].isExcluded)
		{
			rhsValue = INT16_MIN;
		}

		if (lhsValue != rhsValue)
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs == rhs);
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	int16_t prevDiff = lhs.valueByPoint[0].value - rhs.valueByPoint[0].value;

	for (int i = 1; i < constants::INTERVAL_SIZE; i++)
	{
		int16_t newDiff = lhs.valueByPoint[i].value - rhs.valueByPoint[i].value;

		if (prevDiff != newDiff)
		{
			return false;
		}
	}

	return true;
}

ModifiableIntegersFunction operator^(const ModifiableIntegersFunction& func, int16_t k)
{
	ModifiableIntegersFunction result(func);

	// TODO: check for how many times
	for (size_t i = 0; i < k - 1; i++)
	{
		result = result(result);
	}

	return result;
}

ModifiableIntegersFunction operator!(const ModifiableIntegersFunction& func)
{
	ModifiableIntegersFunction result(func);

	if (!result.checkForBijection())
	{
		throw std::invalid_argument("The function is not bijective (injective and surjective)");
	}

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		result.valueByPoint[i].key = func.valueByPoint[i].value;
		result.valueByPoint[i].value = func.valueByPoint[i].key;
	}

	return ModifiableIntegersFunction();
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