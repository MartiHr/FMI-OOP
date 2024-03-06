#include <iostream>
#include <fstream>

const int MAX_TABLE_ROW = 50;
const int MAX_TABLE_COLS = 50;

// TODO: refactor using these structs
struct Cell
{
	int cellValue;
};

struct Row
{
	// exract constant
	Cell* cells;
};

struct Table
{
	// exract constant
	Row* rows;
};

unsigned getCharCountFromFile(std::ifstream& ifs, char soughtChar)
{
	if (!ifs.is_open())
	{
		return 0;
	}

	unsigned int count = 0;

	char current;
	while (!ifs.eof())
	{
		ifs.get(current);
		if (current == soughtChar)
		{
			count++;
		}
	}

	return count + 1;
}

unsigned getRowsCount(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(file, '|');
}

unsigned getColsCount(const char* fileName)
{
	std::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(myFile, ',');
}

void deleteMatrix()
{
	// TODO: implement
}

int** initMatrix(int matrixRows, const char* fileName)
{
	std::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return 0;
	}

	int** matrix = new int* [matrixRows];


}

int** multiplyMatrices(const char* fileName1, const char* fileName2, const char* resultName)
{
	int firstMatrixRows = getRowsCount(fileName1);
	int secondMatrixRows = getRowsCount(fileName2);

	if (firstMatrixRows == 0 || secondMatrixRows == 0)
	{
		return nullptr;
	}

	int** matrix1 = initMatrix(firstMatrixRows);
	int** matrix2 = initMatrix(secondMatrixRows);

	int** resultMatrix = new int* [firstMatrixRows];


}

int main()
{

}