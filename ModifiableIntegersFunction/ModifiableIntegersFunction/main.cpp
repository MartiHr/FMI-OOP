#pragma once
#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t xEqualY(int16_t number)
{
	return number;
}

int16_t cube(int16_t number)
{
	return number * number;
}

int16_t xEqualYPlus1(int16_t number)
{
	return number + 1;
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

	/*ModifiableIntegersFunction mif1(&xEqualY);
	ModifiableIntegersFunction mif2(&cube);
	ModifiableIntegersFunction mif3(&xEqualYPlus1);

	ModifiableIntegersFunction mif4 = mif1 + mif1;
	ModifiableIntegersFunction mif5 = mif1 - mif1;
	mif1.printFirst50();
	std::cout << std::endl;
	mif4.printFirst50();
	std::cout << std::endl;
	mif5.printFirst50();*/

	//Custom result
	/*mif1.setCustomResult(1, 2);
	std::cout << mif1(1) << std::endl;*/

	// Exclude point
	/*std::cout << mif1(1) << std::endl;

	mif1.excludePoint(1);
	try
	{
		mif1(1);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}*/

	// Composition
	/*try
	{
		std::cout << mif1(mif1(2)) << std::endl;
		std::cout << mif1(mif2(2)) << std::endl;
		std::cout << mif2(mif2(2)) << std::endl;
		mif1.excludePoint(4);
		std::cout << mif1(mif2(2)) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}*/

	// < > == !=  
	//std::cout << (mif1 > mif3);

	// Check parralel
	//std::cout << (mif1 || mif3) << std::endl;
	//std::cout << (mif1 || mif2) << std::endl;

	// Check for f^k(x) = f(f(f…f(f(x))...))
	/*ModifiableIntegersFunction mif4 = mif3^3;
	mif3.printFirst50();
	std::cout << std::endl;
	mif4.printFirst50();*/

	// Check for f^-1
	/*ModifiableIntegersFunction mif4 = !mif1;
	mif1.printFirst50();
	std::cout << std::endl;
	mif4.printFirst50();*/

	// Check for injection...
	/*std::cout << mif1.checkForInjection() << std::endl;
	std::cout << mif1.checkForSurjection() << std::endl;
	std::cout << mif1.checkForBijection() << std::endl;*/
	
	// Check serialization and deserialization
	/*ModifiableIntegersFunction mif4(mif2);
	mif1.serialize("file.dat");
	mif4.deserialize("file.dat");
	
	mif1.printFirst50();
	std::cout << std::endl;
	mif4.printFirst50();*/

	// Test printing
	//mif1.printFirst50();
	/*try
	{
		mif2.printFunctionInPlane(-10, 10, -10, 10);
		mif1.printFunctionInPlane(-10, 10, -11, 10);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}*/
}