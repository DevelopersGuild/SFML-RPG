#include "GameSystem.h"
#include "GameNetwork.h"
#include "ResourcePath.h"
#include <algorithm>

using namespace Gameplay;

GameSystem::GameSystem(Configuration& newConfig) :
	config(newConfig),
	map(resourcePath() + "maps")
{
	//create the player
	//TBD, players should be in the std::map
	player.reset(new Player(config, config.player_name, "asdf"));

	//load the map
	//TBD, load every map needed
	map.Load("test.tmx");
	
	//place every player in the corner of the map
	//TBD, only testing map available
	auto& layerVector = map.GetLayers();
    auto playerLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Player";
	});

	if (playerLayer == layerVector.end())
		throw "not found!";

	tmx::MapObject playerObj;
	playerObj.SetShapeType(tmx::MapObjectShape::Rectangle);
	playerObj.SetSize(sf::Vector2f(20, 12));
	playerObj.SetPosition(-50, -50);
	playerObj.AddPoint(sf::Vector2f());
	playerObj.AddPoint(sf::Vector2f(20, 0));
	playerObj.AddPoint(sf::Vector2f(20, 12));
	playerObj.AddPoint(sf::Vector2f(0, 12));
	playerObj.CreateDebugShape(sf::Color::Blue);
	playerObj.SetName(player->getName());

	playerLayer->objects.push_back(std::move(playerObj));
	addPlayertoMap("test.tmx", "event_start");
}

void Gameplay::GameSystem::addPlayertoMap(const std::string & mapName, const std::string & locationName)
{
	//mapName TBD
	//...

	player->changeMap(&map, locationName);
}
