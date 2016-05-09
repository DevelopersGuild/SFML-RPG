#include "GameSystem.h"
#include "GameNetwork.h"
#include "GameInterface.h"
#include "ResourcePath.h"
#include <algorithm>

using namespace Gameplay;

GameSystem::GameSystem(Configuration& newConfig) :
	config(newConfig)
{
	//create the players
	//TBD, players should be in the std::map
	player.reset(new Player(config, config.player_name, config.player_name));

	//load the map
	//TBD, load every map needed
	loadMap("test.tmx");

	addPlayertoMap("test.tmx", "event_start");

	//set current map camera on this computer
	currentMap = mapTree["test.tmx"];
}

void Gameplay::GameSystem::movePlayer(const Character::Direction & direction)
{
	tmx::MapObject* eventObject = player->moveCharacter(direction);

	//if pointer points to a event object, handle event
	if (eventObject)
	{
		handleGameEvent(eventObject);
	}
}

void Gameplay::GameSystem::addPlayertoMap(const std::string & mapName, const std::string & locationName)
{
	//mapName TBD
	//...
	tmx::MapLoader* map = mapTree.at(mapName);
	player->changeMap(map, locationName);
}

void Gameplay::GameSystem::handleGameEvent(tmx::MapObject* eventObject)
{
	//Test only
	if (eventObject->GetType() == "dialogue")
	{
		std::cout << "Test dialogue: " << eventObject->GetPropertyString("content") << std::endl;
	}
	else if (eventObject->GetType() == "teleport")
	{
		std::cout << "Test dialogue: " << eventObject->GetPropertyString("destination") << std::endl;
		interfacePtr->setTransition();
		interfacePtr->exitTransition();
	}
}

void Gameplay::GameSystem::loadMap(const std::string & filename)
{
	tmx::MapLoader* newMap = new tmx::MapLoader(resourcePath() + "maps");

	if (!newMap->Load(filename))
	{
		throw "Map " + filename + " not found!";
	}

	//place every player in the corner of the map
	//TBD, only testing map available
	auto& layerVector = newMap->GetLayers();
	auto playerLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Player";
	});

	if (playerLayer == layerVector.end())
		throw "not found!";

	//create a map object representing player
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

	//push the map into the tree
	mapTree.emplace(filename, std::move(newMap));
	
}
