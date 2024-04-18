#pragma once
#include <iostream>
#include <exception>
#include "ModifiableIntegersFunction.h"

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*pred)(int16_t number)) : function(pred)
{
	for (int i = 0; i < 100; ++i)
	{
		customResults[i] = -1; // Default value indicating no custom result
		excludedPoints[i] = false; // Default value indicating not excluded
	}
}

void ModifiableIntegersFunction::setCustomResult(int16_t input, int16_t result)
{
	customResults[input] = result; // Map input to array index
}

void ModifiableIntegersFunction::excludePoint(int16_t point)
{
	excludedPoints[point] = true; // Map input to array index
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const
{
	bool isExcluded = excludedPoints[input];

	if (isExcluded)
	{
		throw std::invalid_argument("This point is excluded");
	}

	int16_t custom = customResults[input];

	if (custom != -1)
	{
		return custom;
	}

	return function(input);
}


