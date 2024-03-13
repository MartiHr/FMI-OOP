#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_NAME_LEN = 50;
const int BUFFER_SIZE = MAX_NAME_LEN + 1;
const int LEAST_POWER = 10;
const int MAX_POWER = 1000;

constexpr char FILE_NAME[] = "pokemons.dat";

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
		std::cout << "Invalid input";
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

void writePokemonToBinary(std::ofstream& file, Pokemon& pokemon)
{
	if (!file.is_open())
	{
		std::cout << "File not open";
		return;
	}

	file.write((const char*)&pokemon, sizeof(pokemon));
}

void readPokemonFromBinary(std::ifstream& file, Pokemon& pokemon)
{
	if (!file.is_open())
	{
		std::cout << "File did not open";
		return;
	}

	file.read((char*)&pokemon, sizeof(pokemon));
}


struct PokemonHandler
{
	const char* filename;
};

PokemonHandler newPokemonHandler(const char* filename)
{
	PokemonHandler ph;

	if (!filename)
	{
		ph.filename = " ";
		return ph;
	}

	ph.filename = filename;
	return ph;
}

int size(const PokemonHandler& ph)
{
	std::ifstream file(ph.filename);

	if (!file.is_open())
	{
		return -1;
	}

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	return fileSize / sizeof(Pokemon);
}

int main()
{
	// Read a pokemon from the standard input and print it
	Pokemon p1;
	char name[] = "Pikachu";
	initPokemon(p1, name, Type::ELECTRIC, 10);
	printPokemon(p1);

	// Write a pokemon to a binary file
	std::ofstream outFile(FILE_NAME, std::ios::binary);
	writePokemonToBinary(outFile, p1);
	outFile.close();

	// Read a pokemon from a binary file
	std::ifstream inFile(FILE_NAME, std::ios::binary);
	Pokemon p2;
	readPokemonFromBinary(inFile, p2);
	printPokemon(p2);
	inFile.close();

	//Pokemon handler functions

	// Create a pokemon handler
	PokemonHandler ph = newPokemonHandler(FILE_NAME);

	// Number of pokemons 
	std::cout << size(ph);
}