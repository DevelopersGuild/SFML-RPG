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
		}
        
		void add(sf::IntRect&& newRect)
        {
            spriteList.push_back(newRect);
            it = spriteList.begin(); //reset the iterator to prevent error
        }

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

        //Character's max HP
        int max_hp;
        
		//Character's current HP
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

		//the distance that character moved after the latest battle
		int distance_since_lastBattle;
	public:
		Character(Configuration& newConfig);

		Character(Configuration& newConfig, const std::string& newName);

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

		//get the distance that character has moved since the latest battle
		int getDistance_lastBattle() { return distance_since_lastBattle; }

		//set the distance that character has moved since the latest battle
		void setDistance_lastBattle(int value) { distance_since_lastBattle = value; }
        
        //set the speed of character
        void setSpeed(float newSpeed) { speed = newSpeed; }
        
        //get the speed of character
        float getSpeed() { return speed; }
        
        //set the attack value of character
        void setAtk(const int& value){atk = value;}
        
        //get tthe attack value of character
        int getAtk(){return atk;}
        
        //set the defence value of character
        void setDef(const int& value){def = value;}
        
        //get the defence value of character
        int getDef(){return def;}
        
        //set the character's current hp. If value is greater than maxHp, it will set to maxHp only.
        void setCurrentHp(const int& value);
        
        //get the current Hp of character
        int getCurrentHp(){return hp;}
        
        //set the maximum hp of character
        void setMaxHp(const int& value);
        
        //get the maximum hp of character
        int getMaxHp(){return max_hp;}
	};
}
#endif