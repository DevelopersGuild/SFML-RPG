#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Character.h"

class Skill
{
private:
	std::string name;
	Character* character;	// Character that owns the skill.
	int attackBonus;
	int defenceBonus;
	int speedBonus;
	int levelRequirement;	// Level required to use skill.
	double cost;	// Money required to buy skill.

public:
	Skill();

};

#endif