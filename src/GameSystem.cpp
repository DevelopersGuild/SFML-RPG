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
    loadMap("Test2.tmx");

	addPlayertoMap("test.tmx", "event_start");
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
	currentMap = mapTree.at(mapName);
	player->changeMap(currentMap, locationName);
}

void Gameplay::GameSystem::handleGameEvent(tmx::MapObject* eventObject)
{
	if (eventObject->GetType() == "teleport")
	{
		interfacePtr->setTransition();
        addPlayertoMap(eventObject->GetPropertyString("destination"), "event_start");
		interfacePtr->exitTransition();
	}
    else if(eventObject->GetType() == "dialogue")
    {
        std::cout << eventObject->GetPropertyString("content") << std::endl;
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

void Gameplay::GameSystem::interact()
{
    //ask player to "interect".
    tmx::MapObject* eventObj = player->interact();
    
    //if eventObj is not null, handle event.
    if(eventObj)
    {
        handleGameEvent(eventObj);
    }
}
