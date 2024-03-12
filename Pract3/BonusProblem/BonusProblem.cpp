#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>

const int MAX_NAME_LEN = 50;
const int BUFFER_SIZE = MAX_NAME_LEN + 1;
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
	char name[MAX_NAME_LEN + 1];
	Type type;
	unsigned power;
};

void initPokemon(Pokemon& pokemon, char name[MAX_NAME_LEN], Type type, unsigned power)
{
	if (power < 10 || power > 100)
	{
		std::cout << "Invalid power";
		return;
	}

	strcpy(pokemon.name, name);
	pokemon.type = type;
	pokemon.power = power;
}

// Print the type of the pokemon
void printType(Type type)
{
	switch (type)
	{
	case Type::NORMAL:
		std::cout << "Normal" << std::endl;
		break;
	case Type::FIRE:
		std::cout << "Fire" << std::endl;
		break;
	case Type::WATER:
		std::cout << "Water" << std::endl;
		break;
	case Type::GRASS:
		std::cout << "Grass" << std::endl;
		break;
	case Type::ELECTRIC:
		std::cout << "Electric" << std::endl;
		break;
	case Type::GHOST:
		std::cout << "Ghost" << std::endl;
		break;
	case Type::FLYING:
		std::cout << "Flying" << std::endl;
		break;
	}
}

void printPokemon(Pokemon& pokemon)
{
	std::cout << pokemon.name << std::endl;
	printType(pokemon.type);
	std::cout << pokemon.power << std::endl;
}

int main()
{
	Pokemon p;
	char name[MAX_NAME_LEN] = "Pikachu";
	initPokemon(p, name, Type::ELECTRIC, 10);
	printPokemon(p);


}