#pragma once
#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t cube(int16_t number)
{
	return number * number;
}

int main()
{
	ModifiableIntegersFunction mif(&cube);
	std::cout << mif(1);
}