#pragma once
#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t xEqualY(int16_t number)
{
	return number * number * number - 3 * number;
}

int16_t cube(int16_t number)
{
	return number * number;
}

int main()
{
	/*std::cout << INT16_MAX * 2 + 2 << std::endl;
	ModifiableIntegersFunction mif(&cube);
	std::cout << mif(1) << std::endl;
	mif.excludePoint(2);
	try
	{
		std::cout << mif(2);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::cout << mif(10) << std::endl;
		mif.setCustomResult(10, 101);
		std::cout << mif(10) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}*/

	ModifiableIntegersFunction mif1(&xEqualY);
	ModifiableIntegersFunction mif2(&cube);

	std::cout << mif1.checkForInjection();
	std::cout << mif1.checkForSurjection();
	std::cout << mif1.checkForBijection();

	//mif.printFirst50();
	/*try
	{
		mif1.printFunctionInPlane(-10, 10, -10, 10);
		mif1.printFunctionInPlane(-10, 10, -11, 10);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}*/
}