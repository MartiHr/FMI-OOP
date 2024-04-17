#include <iostream>
#include "MultiSet.h";

int main()
{
	//int n, k;
	//std::cin >> n >> k;
	//MultiSet ms(n, k);
	//std::cout << std::endl << ms.getNumberOccurences(0);

	MultiSet ms2(0, 2);
	std::cout  << ms2.getNumberOccurences(0) << std::endl;

	ms2.add(0);
	ms2.add(0);
	ms2.add(0);
	std::cout << ms2.getNumberOccurences(0) << std::endl;
	// TODO: validate for numbers


}
