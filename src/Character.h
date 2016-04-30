#ifndef CHARACTER_H
#define CHARACTER_H
#include "Item.h"

namespace Gameplay
{
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
		int level;
		Item* items;
	public:
		Hero(std::string name, int hp, int att, int def, int spd, double money, Item* item);
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
}
#endif