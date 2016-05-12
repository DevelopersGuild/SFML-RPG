#ifndef GameSystem_h
#define GameSystem_h

#include "Player.h"
#include "Configuration.h"
#include "StartInfo.h"

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
		GameInterface* interfacePtr;
	protected:
		Configuration& config;

		Player* thisPlayerPtr;
		//a tree of players(every player should have unique name)
		std::map<std::string, Player> playerTree;

		//a tree of maps(using filename as key)
		std::map<std::string, tmx::MapLoader*> mapTree;
		tmx::MapLoader* currentMap;	//the current map camera on this computer
	public:
        GameSystem(Configuration& config, std::unique_ptr<StartInfo>& startInfo);
		GameSystem(const GameSystem&) = delete;
		GameSystem operator=(const GameSystem&) = delete;
		GameSystem(const GameSystem&&) = delete;

		//move the player in the current map
		void movePlayer(const Character::Direction& direction);

		//set the network pointer to Network module
		void setNetworkPtr(GameNetwork* ptr) { networkPtr = ptr; }

		//set the interface pointer to Interface module
		void setInterfacePtr(GameInterface* ptr) { interfacePtr = ptr; }

		//add the player to the target map
		void addPlayertoMap(const std::string& mapName, const std::string& location);

		//handle game events
		void handleGameEvent(tmx::MapObject* eventObject);
        
        //interact with objects
        void interact();

		//update the quadTree of current map
		//see tmx::QuadTree
		void updateQuadTree();

		//add map into the system
		//note: only call this function when all players are initialized!
		void loadMap(const std::string& filename);
	};
}
#endif /* GameSystem_h */
