#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include <string>
#include <vector>

class Player
{
private:
	std::string name;
	// Ingame* ingame;
	Character* character;
	// std::vector<Achievement> achv;
};

#endif