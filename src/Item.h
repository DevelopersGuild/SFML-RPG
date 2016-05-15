#ifndef ITEM_H
#define ITEM_H
#include <string>

namespace Gameplay
{
	class Item
	{
	private:
		std::string name;
		std::string itemDescription;
		int lvl;	// requires certain level to use item
		double price;
	public:
		virtual void useItem() = 0;
	};

	class Armor : public Item
	{
	private:
		int defenceBonus;
	public:
		void useItem();

	};

	class Weapon : public Item
	{
	private:
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
}
#endif