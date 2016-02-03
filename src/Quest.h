#ifndef QUEST_H
#define QUEST_H
#include <string>
#include "Character.h"

class Quest
{
private:
	std::string name;
	std::string description;
	Character* character;
	// Ingame* ingame;
	int levelRequirement;
	double moneyReward;
	int expReward;

public:
	Quest(std::string name, std::string description, int lvl, double money, int exp);
	void completeQuest(Character* character);	// Add reward to character after quest is complete.
};

#endif