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

int main()
{
	Pokemon p;
	char name[] = "Pikachu";
	initPokemon(p, "Pikachu", Type::ELECTRIC, 10);

}