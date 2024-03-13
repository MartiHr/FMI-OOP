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
		std::cout << "Invalid input" << std::endl;
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
		std::cout << "File not open" << std::endl;
		return;
	}

	file.write((const char*)&pokemon, sizeof(pokemon));
}

void readPokemonFromBinary(std::ifstream& file, Pokemon& pokemon)
{
	if (!file.is_open())
	{
		std::cout << "File did not open" << std::endl;
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
	ph.filename = " ";

	if (!filename)
	{
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

	int currentG = file.tellg();
	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(currentG);

	return fileSize / sizeof(Pokemon);
}

Pokemon at(const PokemonHandler& ph, int i)
{
	int sizeOfCollection = size(ph);

	Pokemon p;
	strcpy(p.name, " ");
	p.power = 0;
	p.type = Type::NORMAL;


	if (i < 0 || i >= sizeOfCollection)
	{
		std::cout << "Index outside of bounds" << std::endl;
	}

	std::ifstream file(ph.filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File did not open" << std::endl;
		return p;
	}

	file.seekg(sizeof(Pokemon) * i, std::ios::beg);
	readPokemonFromBinary(file, p);

	return p;
}

void swap(const PokemonHandler& ph, int i, int j)
{
	int sizeOfCollection = size(ph);

	if (i < 0 || i >= sizeOfCollection || j < 0 || j >= sizeOfCollection)
	{
		std::cout << "Index outside of bounds" << std::endl;
		return;
	}

	Pokemon first = at(ph, i);
	Pokemon second = at(ph, j);

	std::ofstream file(ph.filename, std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	int currentP = file.tellp();

	file.seekp(j * sizeof(Pokemon), std::ios::beg);
	writePokemonToBinary(file, first);

	file.seekp(i * sizeof(Pokemon), std::ios::beg);
	writePokemonToBinary(file, second);

	file.seekp(currentP, std::ios::beg);
}

int main()
{
	// Read a pokemon from the standard input and print it
	Pokemon p1;
	char name1[] = "Pikachu";
	initPokemon(p1, name1, Type::ELECTRIC, 10);
	printPokemon(p1);

	Pokemon p2;
	char name2[] = "Charizard";
	initPokemon(p2, name2, Type::FIRE, 30);
	printPokemon(p2);

	// Write a pokemon to a binary file
	std::ofstream outFile(FILE_NAME, std::ios::binary);
	writePokemonToBinary(outFile, p1);
	writePokemonToBinary(outFile, p2);
	outFile.close();

	// Read a pokemon from a binary file
	std::ifstream inFile(FILE_NAME, std::ios::binary);
	Pokemon pokemonFromBinary;
	readPokemonFromBinary(inFile, pokemonFromBinary);
	printPokemon(pokemonFromBinary);
	inFile.close();

	//Pokemon handler functions

	// Create a pokemon handler
	PokemonHandler ph = newPokemonHandler(FILE_NAME);

	// Number of pokemons 
	std::cout << size(ph) << std::endl;

	// Print pokemon at index
	Pokemon invalid = at(ph, -1);
	Pokemon newP = at(ph, 1);
	printPokemon(newP);

	// Swap pokemons
	Pokemon first = at(ph, 0);
	printPokemon(first);

	Pokemon second = at(ph, 1);
	printPokemon(second);

	swap(ph, 1, 2);
	swap(ph, 0, 1);
	
	first = at(ph, 0);
	second = at(ph, 1);
	
	printPokemon(first);
	printPokemon(second);

	return 0;
}