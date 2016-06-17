#include "Item.h"

Gameplay::Item::Item(int price)
{
	description = "";
	name = "";
}

Gameplay::Item::Item(const Item & newItem) :
	price(newItem.price),
	sprite(newItem.sprite),
	description(newItem.description),
	name(newItem.name)
{
}

Gameplay::Item& Gameplay::Item::operator=(const Item & newItem)
{
	Gameplay::Item::Item(newItem);
	return *this;
}

Gameplay::Potion::Potion(int hp_effect) : hp(hp_effect)
{
}

Gameplay::Potion::Potion(const Potion & newPotion) : hp(newPotion.hp)
{
}

Gameplay::Potion& Gameplay::Potion::operator=(const Potion & newPotion)
{
	Gameplay::Potion::Potion(newPotion);
	return *this;
}

Gameplay::Equip::Equip()
{
	hp_bonus = 0;
	def_bonus = 0;
	atk_bonus = 0;
	hp_multiplier = 0;
	def_multiplier = 0;
	atk_multiplier = 0;
	speed_multiplier = 0;
	battleSpeed_multiplier = 0;
}

Gameplay::Equip::Equip(const Equip & newEquip)
{
	this->hp_bonus = newEquip.hp_bonus;
	this->def_bonus = newEquip.def_bonus;
	this->atk_bonus = newEquip.atk_bonus;
	this->hp_multiplier = newEquip.hp_multiplier;
	this->def_multiplier = newEquip.def_multiplier;
	this->atk_multiplier = newEquip.atk_multiplier;
	this->speed_multiplier = newEquip.speed_multiplier;
	this->battleSpeed_multiplier = newEquip.battleSpeed_multiplier;
}

Gameplay::Equip& Gameplay::Equip::operator=(const Equip & newEquip)
{
	Gameplay::Equip::Equip(newEquip);
	return *this;
}

Gameplay::ItemLoader::ItemLoader(Configuration & newConifg) : config(newConifg)
{
	//minor potion
	Potion minorPotion;
	minorPotion.setName("minorPotion");
	minorPotion.setDescription("Revive 100 hp.");
	minorPotion.setHpEffect(50);
	minorPotion.setTexture(config.texMan.get("IconSet.png"));
	minorPotion.setIntRect(sf::IntRect(32, 832, 32, 32));
	minorPotion.setPrice(50);
	itemTree.emplace(minorPotion.getName(), minorPotion);

	//medium potion
	Potion mediumPotion;
	mediumPotion.setName("mediumPotion");
	mediumPotion.setDescription("Revive 200 hp.");
	mediumPotion.setHpEffect(200);
	mediumPotion.setTexture(config.texMan.get("IconSet.png"));
	mediumPotion.setIntRect(sf::IntRect(32, 800, 32, 32));
	mediumPotion.setPrice(100);
	itemTree.emplace(mediumPotion.getName(), mediumPotion);

	//large potion
	Potion largePotion;
	largePotion.setName("largePotion");
	largePotion.setDescription("Revive 500 hp.");
	largePotion.setHpEffect(500);
	largePotion.setTexture(config.texMan.get("IconSet.png"));
	largePotion.setIntRect(sf::IntRect(32, 1024, 32, 32));
	largePotion.setPrice(200);
	itemTree.emplace(largePotion.getName(), largePotion);
}
