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
	public:
		Player(Configuration& config)
		{
			name = "Unnamed player";
			charPtr.reset(new Character(config));
		}

		Player(Configuration& config, const std::string& playerName, const std::string& charName)
		{
			name = playerName;
			charPtr.reset(new Character(config, charName));
		}

		void moveCharacter(const float& x, const float& y){ charPtr->move(x, y);}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*charPtr);
		}
	};
}