#pragma once
#include <iostream>

class ModifiableIntegersFunction
{
	int16_t(*function)(int16_t number);

	// TODO: use them with a vector like class
	// For setting a specific result for a given input
	int16_t customResults[1000]; // Assuming input range is within [-999, 999]

	// For excluding a point
	bool excludedPoints[1000];

public:
	ModifiableIntegersFunction(int16_t(*pred)(int16_t number));

	void setCustomResult(int16_t input, int16_t result);
	void excludePoint(int16_t point);
	int16_t operator()(int16_t input) const;
};