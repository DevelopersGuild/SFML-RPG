#ifndef GameData_h
#define GameData_h

#include <tmx/MapLoader.h>
#include <map>
#include <list>
#include "Player.h"


namespace Gameplay
{
	/*
	GameData class
	Stores the important data for the game.
	*/
	class GameData
	{
	private:
		Configuration& config;

		//std::map<std::string, tmx::MapLoader> gameMap;
		tmx::MapLoader testmap;	//temporary

		std::list<Player> playerList;	//testing only, TBD
	public:
		GameData(Configuration& config);
		tmx::MapLoader& getMap() { return testmap; }
		std::list<Player>& getPlayerList() { return playerList; }
		void moveCharacter(const float& x, const float& y)
		{
			for (Player& player : playerList)
			{
				player.moveCharacter(x, y);
			}
		}
	};
}
#endif /* GameData_h */
