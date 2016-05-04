#ifndef GameSystem_h
#define GameSystem_h

#include "Player.h"
#include "Configuration.h"

namespace Gameplay
{
	//forward declaration of GameNetwork
	class GameNetwork;

	//forward declaration of GameInterface
	class GameInterface;

	/*
	GameSystem class
	Base class for processing and managing game data.
	*/
	class GameSystem
	{
		friend GameInterface;
	private:
		GameNetwork* networkPtr;
	protected:
		Configuration& config;

		std::unique_ptr<Player> player;

		//once loaded, the map cannot be changed
		tmx::MapLoader map;
	public:
		GameSystem(Configuration& config);
		GameSystem(const GameSystem&) = delete;
		GameSystem operator=(const GameSystem&) = delete;
		GameSystem(const GameSystem&&) = delete;

		//move the player in the current map
		void movePlayer(const Character::Direction& direction) { player->moveCharacter(direction); }

		//set the network pointer to Network module
		void setNetworkPtr(GameNetwork* ptr) { networkPtr = ptr; }

		//add the player to the target map
		void addPlayertoMap(const std::string& mapName, const std::string& location);
	};
}
#endif /* GameSystem_h */
