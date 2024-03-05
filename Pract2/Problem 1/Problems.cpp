#include <iostream>
#include <fstream>

//Problem 1:
void printSumFromFile(const char* fileName) 
{
    if (!fileName)
    {
        return;
    }

    std::ifstream fileStream(fileName);

    if (!fileStream.is_open())
    {
        std::cout << "The file could not open!" << std::endl;
        return;
    }
    
    int num;
    int sum = 0;

    while (!fileStream.eof())
    {
        fileStream >> num;
        sum += num;
    }

    std::cout << sum << std::endl;

    fileStream.close();
}

//Problem 2:
unsigned findMaxNumFromFile(const char* fileName) 
{
    if (!fileName)
    {
        return 0;
    }

    std::ifstream fileStream(fileName);

    if (!fileStream.is_open())
    {
        std::cout << "The file could not open!" << std::endl;
        return 0;
    }

    int maxNumber = INT_MIN;
    int current;

    while (!fileStream.eof())
    {
        fileStream >> current;

        if (current > maxNumber)
        {
            maxNumber = current;
        }
    }

    return maxNumber;
}

unsigned findCountOfSymbol(const char* fileName, const char soughtSymbol)
{
    if (!fileName)
    {
        return 0;
    }

    std::ifstream fileStream(fileName);

    if (!fileStream.is_open())
    {
        std::cout << "The file could not open!" << std::endl;
        return 0;
    }

    char character;
    unsigned count = 0;
    while (!fileStream.eof())
    {
        fileStream.get(character);

        if (character == soughtSymbol)
        {
            count++;
        }
    }

    return count;
}

//Problem 3:
unsigned getLinesCount(const char* fileName) 
{
    if (!fileName)
    {
        return 1;
    }

    return findCountOfSymbol(fileName, '\n');
}

int main() 
{
    printSumFromFile("sum.txt");
    std::cout<< findMaxNumFromFile("maxNumber.txt") <<std::endl;
    std::cout<< getLinesCount("symbolFile.txt") <<std::endl;
}