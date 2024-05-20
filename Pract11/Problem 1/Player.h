#pragma once

enum class Stars
{
	one,
	two,
	three,
	four,
	five
};

class Player
{
private:
	unsigned ID = 0;
	unsigned points = 0;
	Stars stars = Stars::one;
	
protected:
	bool levelUp();

public:
	Player() = default;

};