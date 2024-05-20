#pragma once
#include "Player.h"

class Guest : public Player
{
private:
	// seconds
	long remainingTime;
	
public:
	Guest(long remainingTime);
};