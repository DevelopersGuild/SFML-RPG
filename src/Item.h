#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	class Item
    {
    private:
        int price;
        sf::Sprite sprite;
        std::string description;
    public:
        Item(int price = 1);
        Item(const Item&);
        Item& operator=(const Item&);
        
        void setIntRect(const sf::IntRect& rect){sprite.setTextureRect(rect);}
        const sf::IntRect& getIntRect(){return sprite.getTextureRect();}
        void setTexture(const sf::Texture& texture){sprite.setTexture(texture);}
        const sf::Texture* getTexture(){return sprite.getTexture();}
        void setPrice(int value){price = value;}
        int getPrice(){return price;}
        void setDescription(const std::string& str){description = str;}
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
}
#endif