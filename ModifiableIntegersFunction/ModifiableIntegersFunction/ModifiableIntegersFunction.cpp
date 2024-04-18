#pragma once
#include <iostream>
#include "ModifiableIntegersFunction.h"

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t (*pred)(int16_t number)) : function(pred) 
{
    for (int i = 0; i < 1000; ++i) 
    {
        customResults[i] = -1; // Default value indicating no custom result
        excludedPoints[i] = false; // Default value indicating not excluded
    }
}

void ModifiableIntegersFunction::setCustomResult(int16_t input, int16_t result)
{
    customResults[input + 999] = result; // Map input to array index
}

void ModifiableIntegersFunction::excludePoint(int16_t point)
{
    excludedPoints[point] = true; // Map input to array index
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const
{
    // TODO: fix after implementing resizable array
    for (int i = -999; i < 999; i++)
    {

    }
    if (customResults[input + 999] != -1) 
    {
        return customResults[input + 999];
    }

    // Check for excluded point
    if (excludedPoints[input + 999]) 
    {
        // Here you can return an error or a special signal
    }

    // Return the result of the function
    return function(input);
}


