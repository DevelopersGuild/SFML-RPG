#ifndef ITEM_H
#define ITEM_H
#include "MagicType.h"
#include <string>
#include <vector>

class Item
{
private:
	std::string name;
	std::string itemDescription;
	int lvl;	// requires certain level to use item
	double value;	// price of item.
public:
	virtual void useItem() = 0;
};

class Armor : public Item
{
private:
	std::vector<MagicType> type;
	int defenceBonus;
public:
	void useItem();

};

class Weapon : public Item
{
private:
	std::vector<MagicType> type;
	int attackBonus;
public:
	void useItem();
};

class Potion : public Item
{
private:
	int healthBonus;
public:
	void useItem();
};
#endif