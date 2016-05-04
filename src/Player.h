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
		//the name of the player(not character)
		std::string name;

		//a vector of items
		std::vector<Item> item;

		//Team pointer...TBD

		//the pointer to the character that controlled by this player
		std::unique_ptr<Character> charPtr;

		//the pointer to the current map
		tmx::MapLoader* currentMap;
	public:
		Player(Configuration& config);

		Player(Configuration& config, const std::string& playerName, const std::string& charName);

		void moveCharacter(const Character::Direction& direction);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setCharacterPosition(sf::Vector2f& position) { charPtr->setPosition(position); }

		const sf::Vector2f& getPosition() { return charPtr->getPosition(); }

		const std::string& getName() { return name; }

		void changeMap(tmx::MapLoader* map, const std::string location);

		tmx::MapLoader* getMap() { return currentMap; }
	};
}