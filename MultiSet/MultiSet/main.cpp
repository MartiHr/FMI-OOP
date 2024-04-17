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

	/*Добавяне на число.
	Проверка колко пъти се съдържа число.
	Принтиране на всички числа, които се съдържат в мултимножеството.
	Принтиране на това как мултимножеството е представено в паметта.
	Сериализация / десериализация в / от двоичен файл.
	Сечение / Разлика на две мултимножества.
	Допълнение на мултимножество(ако x се е срещал p пъти,
		то в допълнението се среща 2 ^ k - 1 - p пъти).*/
}
