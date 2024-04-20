#pragma once
#include <iostream>
#include <exception>
#include <fstream>
#include "ModifiableIntegersFunction.h"
#include "GlobalConstants.h"

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	function = other.function;
	valueByPoint = new KeyValue[constants::INTERVAL_SIZE];

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
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

void ModifiableIntegersFunction::printFirst50() const
{
	/*for (size_t i = 0; i < 5; i++)
	{
		std::cout << valueByPoint[i].key << "->" << valueByPoint[i].value << ' ';
	}*/

	for (size_t i = (-INT16_MIN); i < 5 + (-INT16_MIN); i++)
	{
		std::cout << valueByPoint[i].key << ":" << valueByPoint[i].value << ' ';
	}
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
		valueByPoint[i].value = function(valueByPoint[i].key);
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
		throw std::invalid_argument(constants::EXCLUDED_POINT);
	}

	int16_t result = valueByPoint[input + -(INT16_MIN)].value;
	return result;
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
		int setIndex = innerRes + (-INT16_MIN);
		result.valueByPoint[i].value = valueByPoint[setIndex].value;
	}

	return result;
}

bool ModifiableIntegersFunction::checkForInjection()
{
	bool* encounteredValues = new bool[constants::INTERVAL_SIZE] { false };

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		if (valueByPoint[i].isExcluded)
		{
			continue;
		}

		int16_t currentValue = valueByPoint[i].value;
		int setIndex = currentValue - INT16_MIN;

		// Check if value is already contained
		if (encounteredValues[setIndex] == true)
		{
			delete[] encounteredValues;
			return false;
		}

		encounteredValues[setIndex] = true;
	}

	delete[] encounteredValues;
	return true;
}

bool ModifiableIntegersFunction::checkForSurjection()
{
	// Check if every value has a key
	bool* foundValues = new bool[constants::INTERVAL_SIZE] { false };

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		if (valueByPoint[i].isExcluded)
		{
			delete[] foundValues;
			return false;
		}

		int16_t currentValue = valueByPoint[i].value;
		int setIndex = currentValue + (-INT16_MIN);

		foundValues[setIndex] = true;
	}

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		if (foundValues[i] == false)
		{
			delete[] foundValues;
			return false;
		}
	}

	delete[] foundValues;
	return true;
}

bool ModifiableIntegersFunction::checkForBijection()
{
	return checkForInjection() && checkForSurjection();
}

void ModifiableIntegersFunction::serialize(const char* fileName) const
{
	if (!fileName)
	{
		throw std::invalid_argument(constants::NULL_FILENAME);
	}

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		throw std::runtime_error(constants::FAILED_TO_OPEN);
	}

	ofs.write((const char*)valueByPoint, constants::INTERVAL_SIZE * sizeof(KeyValue));
}

void ModifiableIntegersFunction::deserialize(const char* fileName)
{
	if (!fileName)
	{
		throw std::invalid_argument(constants::NULL_FILENAME);
	}

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::runtime_error(constants::FAILED_TO_OPEN);
	}

	ifs.read((char*)valueByPoint, constants::INTERVAL_SIZE * sizeof(KeyValue));
}

void ModifiableIntegersFunction::printFunctionInPlane(int16_t x1, int16_t x2, int16_t y1, int16_t y2) const
{
	if (x2 - x1 != 20 || y2 - y1 != 20)
	{
		throw std::invalid_argument(constants::INVALID_DIFFERENCE);
	}

	for (int y = y2; y >= y1; y--)
	{
		for (int x = x1; x < x2; x++)
		{
			if (valueByPoint[x + (-INT16_MIN)].isExcluded == false
				&& valueByPoint[x + (-INT16_MIN)].value == y)
			{
				std::cout << 'O';
			}
			else if (x == 0 && y != 0)
			{
				std::cout << '|';
			}
			else if (y == 0 && x != 0)
			{
				std::cout << '-';
			}
			else if (x == 0 && y == 0)
			{
				std::cout << '|';
			}
			else
			{
				std::cout << ' ';
			}
		}

		std::cout << std::endl;
	}
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
	// If the function are not lines it would show 
	// the function is offset. If somebody thinks it is unwanted behaviour
	// a simple check for line would be sufficient.
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

	// TODO: validate k

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
		throw std::invalid_argument(constants::INVALID_BIJECTION);
	}

	for (int i = 0; i < constants::INTERVAL_SIZE; i++)
	{
		result.valueByPoint[i].key = func.valueByPoint[i].value;
		result.valueByPoint[i].value = func.valueByPoint[i].key;
	}

	return result;
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