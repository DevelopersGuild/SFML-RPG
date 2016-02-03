#ifndef SKILL_H
#define SKILL_H
#include "Character.h"
#include "MagicType.h"
#include <string>

class Skill
{
private:
	std::string name;
	Character* character;	// Character that owns the skill.
	std::vector<MagicType> type;	// Magic type of skill.
	int magicPtRequirement;	// MP required to use skill.
	int levelRequirement;	// Level required to use skill.
	double cost;	// Money required to buy skill.
	int attackBonus;
	int defenceBonus;
	int speedBonus;

public:
	Skill(std::string name, std::vector<MagicType> type, int mp, int lvl,
		double cost, int att, int def, int spd);

};

#endif