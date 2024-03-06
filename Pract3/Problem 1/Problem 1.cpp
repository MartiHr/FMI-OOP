#include <iostream>
#include <fstream>

// TODO: refactor using these structs
struct Cell
{
	int cellValue;
};

struct Row 
{
	// exract constant
	Cell cells[5];
};

struct Table
{
	// exract constant
	Row rows[5];
};

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
	if (!ifs.is_open())
		return 0;

	unsigned int count = 0;

	char current;
	while (!ifs.eof())
	{
		ifs.get(current);
		if (current == ch)\
		{
			count++;
		}
	}

	return count;
}

unsigned getLinesCount(const char* fileName)
{
	std::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(myFile, '\n') + 1;
}

void matrixToArray()
{

}

unsigned multiplyMatrices(const char* fileName1, const char* fileName2, const char* resultName)
{
	std::ifstream ifs1(fileName1);
	std::ifstream ifs2(fileName2);

	if (!ifs1.is_open() || !ifs2.is_open())
	{
		return 0;
	}

	
}



int main()
{

}