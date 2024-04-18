#include <iostream>
#include "MultiSet.h";

int main()
{
	/*MultiSet ms1(0, 2);

	std::cout << ms1.getNumberOccurences(0) << std::endl;

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

	std::cout << ms1.getNumberOccurences(0) << std::endl;*/


	MultiSet ms2(2, 3);
	ms2.add(0);
	ms2.add(1);
	ms2.add(1);
	ms2.add(2);
	ms2.add(2);
	ms2.add(2);

	std::cout << ms2.getNumberOccurrences(0) << std::endl;
	std::cout << ms2.getNumberOccurrences(1) << std::endl;
	std::cout << ms2.getNumberOccurrences(2) << std::endl;

	ms2.printAllNumbers();
}
