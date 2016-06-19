#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Configuration.h"

namespace Gameplay
{
	class Item
    {
    private:
        int price;
		std::string name;
        sf::Sprite sprite;
        std::string description;
    public:
        Item(int price = 1);
        Item(const Item&);
        Item& operator=(const Item&);
        
		void setName(const std::string& newName) { name = newName; }
		const std::string& getName() { return name; }
        void setIntRect(const sf::IntRect& rect){sprite.setTextureRect(rect);}
        const sf::IntRect& getIntRect(){return sprite.getTextureRect();}
        void setTexture(const sf::Texture& texture){sprite.setTexture(texture);}
        const sf::Texture* getTexture(){return sprite.getTexture();}
        void setPrice(int value){price = value;}
        int getPrice(){return price;}
        virtual void setDescription(const std::string& str){description = str;}
        const std::string& getDescription(){return description;}
    };
    
    class Potion : public Item
    {
    private:
        int hp;
    public:
        Potion(int hp_effect = 50);
        Potion(const Potion&);
        Potion& operator=(const Potion&);
        
        void setHpEffect(int value){hp = value;}
        int getHpEffect(){return hp;}
    };

	class Equip : public Item
	{
	private:
		int hp_bonus;
		int def_bonus;
		int atk_bonus;	
		float hp_multiplier;
		float def_multiplier;
		float atk_multiplier;
		float speed_multiplier;
		float battleSpeed_multiplier;
	public:
		Equip();
		Equip(const Equip&);
		Equip& operator=(const Equip&);

		void setHP_Bonus(int value) { hp_bonus = value; }
		void setDef_Bonus(int value) { def_bonus = value; }
		void setAtk_Bonus(int value) { atk_bonus = value; }
		void setHP_Multiplier(float value) { hp_multiplier = value; }
		void setDef_Multiplier(float value) { def_multiplier = value; }
		void setAtk_Multiplier(float value) { atk_multiplier = value; }
		void setSpeed_Multiplier(float value) { speed_multiplier = value; }
		void setBattleSpeed_Multiplier(float value) { battleSpeed_multiplier = value; }

		int getHP_Bonus() { return hp_bonus; }
		int getDef_Bonus() { return def_bonus; }
		int getAtk_Bonus() { return atk_bonus; }
		float getHp_Multiplier() { return hp_multiplier; }
		float getDef_Multiplier() { return def_multiplier; }
		float getAtk_Multiplier() { return atk_multiplier; }
		float getSpeed_Multiplier() { return speed_multiplier; }
		float getBattleSpeed_Multiplier() { return battleSpeed_multiplier; }
	};

	/*
	ItemLoader
	loader the item.
	*/
	class ItemLoader
	{
	private:
		Configuration& config;
		std::map<std::string, Item> itemTree;
	public:
		ItemLoader(Configuration& config);
		Item& get(const std::string& str) { return itemTree.at(str); }
	};
}
#endif