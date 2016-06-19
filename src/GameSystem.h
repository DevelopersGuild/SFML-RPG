#ifndef GameSystem_h
#define GameSystem_h

#include "Player.h"
#include "Configuration.h"
#include "StartInfo.h"
#include "NPC.h"

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
		BattleFactory battleFactory;
		ItemLoader itemLoader;
		
		void reloadNPCRenderLlist();
        void changeNPCDirection(const std::string& name);
	protected:
		Configuration& config;

		Player* thisPlayerPtr;
		//a tree of players(every player should have unique name)
		std::map<std::string, Player> playerTree;
		
		//npc render list, refresh when map is changed
		std::list<std::unique_ptr<NPC>> npcRenderList;

		//a tree of maps(using filename as key)
		std::map<std::string, tmx::MapLoader*> mapTree;
		tmx::MapLoader* currentMap;	//the current map camera on this computer
        std::shared_ptr<Battle> currentBattle;
	public:
        GameSystem(Configuration& config, std::unique_ptr<StartInfo>& startInfo);
		GameSystem(const GameSystem&) = delete;
		GameSystem operator=(const GameSystem&) = delete;
		GameSystem(const GameSystem&&) = delete;

		//set the network pointer to Network module
		void setNetworkPtr(GameNetwork* ptr) { networkPtr = ptr; }

		//set the interface pointer to Interface module
		void setInterfacePtr(GameInterface* ptr) { interfacePtr = ptr; }

		//move the player in the current map
		virtual void movePlayer(const std::string& playerName, const Character::Direction& direction);

		//add the player to the target map
		virtual void addPlayertoMap(const std::string& playerName, const std::string& mapName, const std::string& location);

		//handle game events
		virtual void handleGameEvent(tmx::MapObject* eventObject);
        
        //interact with objects
        virtual void interact();

		//update the quadTree of current map
		//see tmx::QuadTree
		virtual void updateQuadTree();

		//add map into the mapTree
		//note: only call this function when all players are initialized!
		virtual void loadMap(const std::string& filename);

		//set the player "ready"
		virtual void setReady(const std::string& playerName, const bool& newState);

		//set the player's position in the map
		virtual void setPlayerPosition(const std::string& playerName, sf::Vector2f pos);

		//get the position of the currentPlayer
		virtual sf::Vector2f getPlayerPosition() { return playerTree.at(config.player_name).getPosition(); }

		//create battle on the map
        //if the initial plater is the one controlling this computer,
        //set currentBattlePtr to battle
        virtual void createBattle(const std::string& initPlayerName, tmx::MapObject* battleObject);
        
        //delete battle on the map
        virtual void deleteBattle();

		//is the current game in battle?
		virtual bool isInBattle() { return currentBattle.get() != nullptr; }
        
        //is the current battle over?
        bool isBattleOver();
	};
}
#endif /* GameSystem_h */
