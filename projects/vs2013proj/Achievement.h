#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H
#include "Player.h"
#include <string>

class Achievement
{
private:
	std::string name;
	Player* player;

public:
	Achievement(std::string name);
};

#endif