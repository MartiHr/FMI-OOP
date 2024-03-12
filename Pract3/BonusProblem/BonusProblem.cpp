#include <iostream>

const int MAX_NAME_LEN = 50;
const int LEAST_POWER = 10;
const int MAX_POWER = 1000;

enum class Type
{
    NORMAL, 
    FIRE, 
    WATER, 
    GRASS, 
    ELECTRIC, 
    GHOST, 
    FLYING,
};

struct Pokemon
{
    char name[MAX_NAME_LEN];
    Type type;
    unsigned power;
};



int main()
{
    std::cout << "Hello World!\n";
}