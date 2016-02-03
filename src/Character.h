#ifndef CHARACTER_H
#define CHARACTER_H
#include "Player.h"
#include "Item.h"
#include "Status.h"
#include "Skill.h"
#include "Quest.h"
#include <vector>

class Character
{
private:
	Player* player;
	std::string name;
	std::vector<Item> items;
	std::vector<Skill> skills;
	std::vector<Status> status;
	int healthPt;
	int attackPt;
	int defencePt;
	int speedPt;

public:
	Character(std::string nm, int hp, int att, int def, int spd);
	virtual int calculateValue() = 0;	// Calculate total skill points after item bonus.
	virtual int attack() = 0;
};

class Hero : public Character
{
private:
	double money;
	int level;
	int expPoint;
	std::vector<Quest> quests;
public:
	Hero(std::string nm, int hp, int att, int def, int spd, double money) : Character(nm, hp, att, def, spd);
	void levelUp(int exp);	// Increment level and calculate exp points.
};

class Monster : public Character
{
private:
	int level;
};

class NPC : public Character
{
private:
	std::string description;

};
#endif