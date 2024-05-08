#include "Player.h"

bool Player::levelUp()
{
	if (points >= 2048 && stars == Stars::four)
	{
		stars = Stars::five;
		points = 0;
		return true;
	}
	else if (points >= 1024 && stars == Stars::three)
	{
		stars = Stars::four;
		points = 0;
		return true;
	}
	else if (points >= 512 && stars == Stars::two)
	{
		stars = Stars::three;
		points = 0;
		return true;
	}
	else if (points >= 256 && stars == Stars::one)
	{
		stars = Stars::two;
		points = 0;
		return true;
	}
		
	return false;
}
