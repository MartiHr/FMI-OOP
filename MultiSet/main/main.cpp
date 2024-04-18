#pragma once
#include <iostream>
#include "MultiSet.h"


int main()
{
	// Test getNumberOccurences and add
	MultiSet ms1(0, 2);

	//std::cout << ms1.getNumberOccurrences(0) << std::endl;

	ms1.add(0);
	ms1.add(0);
	ms1.add(0);

	try
	{
		ms1.add(1);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	//std::cout << ms1.getNumberOccurrences(0) << std::endl;

	//Test print all numbers
	MultiSet ms2(2, 3);
	ms2.add(0);
	ms2.add(1);
	ms2.add(1);
	ms2.add(2);
	ms2.add(2);
	ms2.add(2);
	// | The other adds are to check if indexes work correct
	// V 
	/* ms2.add(2);
	ms2.add(2);
	ms2.add(2);
	ms2.add(2);
	ms2.add(2)*/;

	//ms2.printAllNumbers();


	// Test print in memory view
	MultiSet ms3(5, 2);
	ms3.add(0);
	ms3.add(1);
	ms3.add(1);
	ms3.add(2);
	ms3.add(2);
	ms3.add(2);
	ms3.add(5);
	//ms3.printMemoryView();


	// Test intersection, diff and complement
	MultiSet ms4(2, 3);
	ms4.add(0);
	ms4.add(0);
	ms4.add(0);
	ms4.add(0);
	ms4.add(1);
	ms4.add(2);
	// { 0 0 0 0 1 2}

	MultiSet ms5(5, 2);
	ms5.add(0);
	ms5.add(0);
	ms5.add(1);
	ms5.add(1);
	ms5.add(2);
	// { 0 0 1 1 2 }

	// expected result { 0 0 1 2 }
	MultiSet intersection = intersect(ms4, ms5);
	//intersection.printAllNumbers();

	// expected result { 0 0 }
	MultiSet diff1 = difference(ms4, ms5);
	//diff1.printAllNumbers();

	// expected result { 0 0 0 шест единици и шест двойки }
	MultiSet complementOfMs4 = ms4.complement();
	//complementOfMs4.printAllNumbers();

	//TEST serialize and deserialize

	ms2.printAllNumbers();
	ms2.serialize("ms.bin");
	MultiSet fromFile(0, 1);
	fromFile.deserialize("ms.bin");
	fromFile.printAllNumbers();
}
