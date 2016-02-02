#ifndef CHARACTER_H
#define CHARACTER_H
#include "Item.h"

class Character
{
private:
	std::string name;
	int healthPt;
	int attackPt;
	int defencePt;
	int speedPt;

public:
	virtual int calculateValue() = 0;
	virtual int attack() = 0;
};

class Hero : public Character
{
private:
	double money;
	Item* items;
};

class Monster : public Character
{
private:

};


#endif