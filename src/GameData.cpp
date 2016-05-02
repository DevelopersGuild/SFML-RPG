#include "GameData.h"
#include "ResourcePath.h"

Gameplay::GameData::GameData(Configuration& newConfig) : 
	config(newConfig),
	testmap(resourcePath() + "maps")
{
	testmap.Load("test.tmx");

	//testing only, TBD
	playerList.push_back(Player(config, config.player_name, "adsf"));
}
