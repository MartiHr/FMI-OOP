#include <iostream>

class BigNumber
{
private:
	int size;
	int capacity;
	char* 
public:
	/**
	 * @brief Default constructor, sets the value of the number to 0
	 */
	BigNumber();

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as a string
	 */
	BigNumber(const char* number);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as an integer
	 */
	BigNumber(long long int number);
};

int main()
{

}
