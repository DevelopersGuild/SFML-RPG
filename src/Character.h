#ifndef CHARACTER_H
#define CHARACTER_H
#include "Item.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "tmx/MapLoader.h"
#include "Configuration.h"

namespace Gameplay
{
	//utitlity class of sprite list
	class SpriteList
	{
	private:
		std::list<sf::IntRect> spriteList;
		std::list<sf::IntRect>::iterator it;
	public:
		SpriteList()
		{
			it = spriteList.begin();
		}
        
		void add(sf::IntRect&& newRect) { spriteList.push_back(newRect); }

		sf::IntRect getNext()
		{
			if (it == spriteList.end())
				it = spriteList.begin();
			return *it++;
		}
        
        sf::IntRect front()
        {
            return spriteList.front();
        }
	};

	class Character : public sf::Drawable
	{
	public:
		//the direction that the character is looking at
		enum Direction { up, down, left, right };
	private:
		//for accessing resourse
		Configuration& config;

		//the pointer to playerObj in the map
		tmx::MapObject* mapCharPtr;

		//the name of the character
		std::string name;

		//Character's HP
		int hp;

		//Character's Attack
		int atk;

		//Character's Defense
		int def;

		//Character's Speed
		float speed;

		//the Character's facing direction
		Direction direction;

		//character's sprite
		sf::Sprite sprite;
        
        //character's name
        sf::Text nameText;

		//the clock to update sprite
		sf::Clock spriteClock;
		float sprite_UpdateRate;

		//moving sprites
		SpriteList upList;
		SpriteList leftList;
		SpriteList rightList;
		SpriteList downList;
	public:
		Character(Configuration& newConfig);

		Character(Configuration& newConfig, const std::string& newName);

		void setSpeed(float newSpeed) { speed = newSpeed; }

		float getSpeed() { return speed; }

		void move(const Direction& newDirection);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setPosition(const sf::Vector2f& position);

		const sf::Vector2f& getPosition() { return sprite.getPosition(); }

		void setCharLayer(tmx::MapObject* ptr) { mapCharPtr = ptr; }

		//get the AABB representation in the map
		sf::FloatRect getAABB();

		//get the colide detection area of this character
		sf::FloatRect getDectionArea();
        
        Direction getDirection(){return direction;}
        
        void setDirection(Direction newDirection);
	};
}
#endif