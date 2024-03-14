#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_NAME_LEN = 50;
const int BUFFER_SIZE = MAX_NAME_LEN + 1;
const int LEAST_POWER = 10;
const int MAX_POWER = 1000;

constexpr char FILE_NAME_BINARY[] = "pokemons.dat";
constexpr char FILE_NAME_TEXT[] = "pokemonsText.txt";

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

void initPokemon(Pokemon& pokemon, char name[MAX_NAME_LEN + 1], Type type, unsigned power)
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
		std::cout << "Normal";
		break;
	case Type::FIRE:
		std::cout << "Fire";
		break;
	case Type::WATER:
		std::cout << "Water";
		break;
	case Type::GRASS:
		std::cout << "Grass";
		break;
	case Type::ELECTRIC:
		std::cout << "Electric";
		break;
	case Type::GHOST:
		std::cout << "Ghost";
		break;
	case Type::FLYING:
		std::cout << "Flying";
		break;
	}
}

void printType(Type type, std::ofstream& file)
{
	switch (type)
	{
	case Type::NORMAL:
		file << "Normal";
		break;
	case Type::FIRE:
		file << "Fire";
		break;
	case Type::WATER:
		file << "Water";
		break;
	case Type::GRASS:
		file << "Grass";
		break;
	case Type::ELECTRIC:
		file << "Electric";
		break;
	case Type::GHOST:
		file << "Ghost";
		break;
	case Type::FLYING:
		file << "Flying";
		break;
	}
}

void printPokemon(Pokemon& pokemon)
{
	std::cout << pokemon.name << std::endl;
	printType(pokemon.type);
	std::cout << std::endl;
	std::cout << pokemon.power << std::endl;
}

void writePokemonToBinary(std::ofstream& file, const Pokemon& pokemon)
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

void insert(const PokemonHandler& ph, const Pokemon& pokemon)
{
	std::ofstream file(ph.filename, std::ios::binary | std::ios::app);

	if (!file.is_open())
	{
		return;
	}

	int current = file.tellp();

	file.seekp(0, std::ios::end);
	writePokemonToBinary(file, pokemon);

	file.seekp(current);
}

void textify(const PokemonHandler& ph, const char* filename)
{
	int sizeOfCollection = size(ph);

	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::cout << "File did not open" << std::endl;
		return;
	}

	for (int i = 0; i < sizeOfCollection; i++)
	{
		Pokemon current = at(ph, i);
		file << current.name << ' ' << current.power << ' ';
		printType(current.type, file);

		if (i != sizeOfCollection - 1)
		{
			file << '\n';
		}
	}

	file.close();
}

Type typeStrToEnum(char str[MAX_NAME_LEN + 1])
{
	Type type;

	if (strcmp(str, "Normal") == 0)
	{
		type = Type::NORMAL;
	}
	else if (strcmp(str, "Fire") == 0)
	{
		type = Type::FIRE;
	}
	else if (strcmp(str, "Water") == 0)
	{
		type = Type::WATER;
	}
	else if (strcmp(str, "Grass") == 0)
	{
		type = Type::GRASS;
	}
	else if (strcmp(str, "Electric") == 0)
	{
		type = Type::ELECTRIC;
	}
	else if (strcmp(str, "Ghost") == 0)
	{
		type = Type::GHOST;
	}
	else if (strcmp(str, "Flying") == 0)
	{
		type = Type::FLYING;
	}
	else
	{
		type = Type::NORMAL;
	}

	return type;
}

void untextify(const PokemonHandler& ph, const char* filename)
{
	std::ifstream ifs(filename);
	std::ofstream ofs(ph.filename, std::ios::binary);

	if (!ifs.is_open() || !ofs.is_open())
	{
		std::cout << "File did not open" << std::endl;
		return;
	}

	char name[MAX_NAME_LEN + 1];
	unsigned power;
	char typeAsStr[MAX_NAME_LEN + 1];

	while (!ifs.eof())
	{
		ifs >> name >> power >> typeAsStr;

		if (power < LEAST_POWER || power > MAX_POWER)
		{
			std::cout << "Invalid power for pokemon " << name << std::endl;
			continue;
		}

		Type type = typeStrToEnum(typeAsStr);
		
		Pokemon current;
		initPokemon(current, name, type, power);
		writePokemonToBinary(ofs, current);
	}
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
	std::cout << std::endl;
	std::ofstream outFile(FILE_NAME_BINARY, std::ios::binary);
	writePokemonToBinary(outFile, p1);
	writePokemonToBinary(outFile, p2);
	outFile.close();

	// Read a pokemon from a binary file
	std::cout << std::endl;
	std::ifstream inFile(FILE_NAME_BINARY, std::ios::binary);
	Pokemon pokemonFromBinary;
	readPokemonFromBinary(inFile, pokemonFromBinary);
	printPokemon(pokemonFromBinary);
	inFile.close();

	//Pokemon handler functions

	// Create a pokemon handler
	PokemonHandler ph = newPokemonHandler(FILE_NAME_BINARY);

	// Number of pokemons 
	std::cout << std::endl;
	std::cout << size(ph) << std::endl;

	// Print pokemon at index
	std::cout << std::endl;
	Pokemon invalid = at(ph, -1);
	Pokemon newP = at(ph, 1);
	printPokemon(newP);

	// Swap pokemons
	std::cout << std::endl;
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

	// Insert pokemon
	std::cout << std::endl;
	insert(ph, p1);
	Pokemon third = at(ph, 2);
	printPokemon(third);

	// Textify
	textify(ph, FILE_NAME_TEXT);

	// Untextify
	untextify(ph, FILE_NAME_TEXT);
	Pokemon pFromText = at(ph, 1);
	std::cout << std::endl;
	printPokemon(pFromText);

	return 0;
}