#pragma once
#include <vector>
#include <memory>
#include "Item.h"
#include "Character.h"
#include "Battle.h"
/*
Player class
The player of the game.
*/
namespace Gameplay
{
	class Player : public sf::Drawable
	{
	public:
		enum STATE { normal, inBattle };
	private:
		Configuration& config;

		//the name of the player
		std::string name;

		//a vector of items
		std::vector<Item> item;

		//Team pointer...TBD

		//the pointer to the character that controlled by this player
		Character character;

		//the pointer to the current map
		tmx::MapLoader* currentMap;

		struct lastSafePlace
		{
			tmx::MapLoader* lastSafeMap;
			std::string lastSafePosition;
		} lastSafePlace;

		//is the player joined(connected) the game
		bool ready;
        
        //state of player: normal, inBattle
		STATE state;

		//the function that determines whether the player will enter a battle or not.
		bool isBattleEncounter();
        
        //the current battle of the player, null is no battle
        std::shared_ptr<Battle> battlePtr;

	public:
		Player(Configuration& config);

		Player(Configuration& config, const std::string& playerName, const std::string& charName);

		/*
		move Character
		if the character is on the cameraMap, perform collision check and move character.
		if the character is not on the cameraMap, move character but no collision check.
		return pointer to the eventObject on the map, return null is no event found.
		*/
		tmx::MapObject* moveCharacter(tmx::MapLoader* cameraMap, const Character::Direction& direction);

		//draw the character on the screen
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//set the position of the character
		void setCharacterPosition(sf::Vector2f& position) { character.setPosition(position); }

		//get the position of the character
		const sf::Vector2f& getPosition() { return character.getPosition(); }

		//get the name of the character
		const std::string& getName() { return name; }

		//get the state of the player
		STATE getState() { return state; }
        
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
        
        //change the state to inBattle.
        void joinBattle(std::shared_ptr<Battle> battle);
        
        //leave the battle and change the state back to normal
        void leaveBattle();

		//teleport the player to the last safe location
		void teleport_ToLastSafeLocation();
        
        //get the direction of the character
        Character::Direction getDirection(){return character.getDirection();}

		//character attributes
		int getCurrentHp() { return character.getCurrentHp(); }
		void setCurrentHp(int value) { character.setCurrentHp(value); }
		int getMaxHp() { return character.getMaxHp(); }
		int getCurrentExp() { return character.getExp(); }
		int getExpCap() { return character.getExpCap(); }
		int getLevel() { return character.getLevel(); }
        int getMoney(){return character.getMoney();}
        void setMoney(int value){return character.setMoney(value);}
	};
}