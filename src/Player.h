#pragma once
#include <vector>
#include <memory>
#include "Item.h"
#include "Character.h"

/*
Player class
The player of the game.
*/
namespace Gameplay
{
	class Player : public sf::Drawable
	{
	private:
		Configuration& config;

		//the name of the player
		std::string name;

		//a vector of items
		std::vector<Item> item;

		//Team pointer...TBD

		//the pointer to the character that controlled by this player
		std::unique_ptr<Character> charPtr;

		//the pointer to the current map
		tmx::MapLoader* currentMap;

		//has to player joined(connected) the game
		bool ready;
	public:
		Player(Configuration& config);

		Player(Configuration& config, const std::string& playerName, const std::string& charName);

		/*
		move Character
		return pointer to the eventObject on the map, return null is no event found.
		*/
		tmx::MapObject* moveCharacter(tmx::MapLoader* currentMap, const Character::Direction& direction);

		//draw the character on the screen
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//set the position of the character
		void setCharacterPosition(sf::Vector2f& position) { charPtr->setPosition(position); }

		//get the position of the character
		const sf::Vector2f& getPosition() { return charPtr->getPosition(); }

		//get the name of the character
		const std::string& getName() { return name; }
        
        //get the event obj that the player is facing
        //return tmx::MapObject if event object is found in player's facing direction. Return NULL is not found.
        tmx::MapObject* interact();

		//reset the map pointer of character and place the character at certain location.
		void changeMap(tmx::MapLoader* map, const std::string location);

		//return the current map of this player
		tmx::MapLoader* getMap() { return currentMap; }

		//is the player ready?
		bool isReady() { return ready; }

		//set playe ready to draw that player on the map
		void setReady(bool boo) { ready = boo; }
	};
}