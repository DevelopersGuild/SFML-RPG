#include "GameSystem.h"
#include "GameNetwork.h"
#include "ResourcePath.h"

using namespace Gameplay;

GameSystem::GameSystem(Configuration& newConfig) :
	config(newConfig),
	map(resourcePath() + "maps")
{
	//testing only
	player.reset(new Player(config, config.player_name, "asdf"));
	map.Load("test.tmx");
}