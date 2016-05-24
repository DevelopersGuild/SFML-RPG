#include "GameSystem.h"
#include "GameNetwork.h"
#include "GameInterface.h"
#include "ResourcePath.h"
#include <algorithm>

using namespace Gameplay;

GameSystem::GameSystem(Configuration& newConfig, std::unique_ptr<StartInfo>& startInfoPtr) :
	config(newConfig)
{
	//create the players
    for(StartInfo::Player& player : startInfoPtr->playerList)
    {
        playerTree.emplace(player.name, Player(config, player.name, player.name));
    }
    thisPlayerPtr = &playerTree.at(config.player_name);

	//load the map
	//TBD, load every map needed
	loadMap("test.tmx");
    loadMap("Test2.tmx");

	for (auto& pair : playerTree)
	{
		addPlayertoMap(pair.second.getName(), "test.tmx", "event_start");
	}
	
}

void Gameplay::GameSystem::movePlayer(const std::string& playerName, const Character::Direction & direction)
{
    Player& player = playerTree.at(playerName);
	tmx::MapObject* eventObject = player.moveCharacter(currentMap, direction);
	
	//if pointer points to a event object, handle event
	if (eventObject && playerName == thisPlayerPtr->getName())
	{
		handleGameEvent(eventObject);
	}
}

void Gameplay::GameSystem::addPlayertoMap(const std::string& playerName, const std::string& mapName, const std::string& location)
{
	//mapName TBD
	//...
	//if the player is the one controling this computer...
	if (playerName == config.player_name)
	{
		currentMap = mapTree.at(mapName);
		Player& player = playerTree.at(playerName);
		player.changeMap(currentMap, location);
	}
	else //if it is another player...
	{
		tmx::MapLoader* newMap = mapTree.at(mapName);
		Player& player = playerTree.at(playerName);
		player.changeMap(newMap, location);
	}
}

void Gameplay::GameSystem::handleGameEvent(tmx::MapObject* eventObject)
{
	if (eventObject->GetType() == "teleport")
	{
		std::string destination = eventObject->GetPropertyString("destination");
		std::string destination_point = eventObject->GetPropertyString("destination_point");
		interfacePtr->setTransition();
        addPlayertoMap(thisPlayerPtr->getName(), destination, destination_point);
		interfacePtr->exitTransition();

		sf::Packet packet;
		packet << "changeMap";
		packet << config.player_name;
		packet << destination << destination_point;

		//if this is client, send the changeMap signal to the server
		if (networkPtr->getServerIP() != sf::IpAddress::None)
		{
			networkPtr->send(networkPtr->getServerIP(), packet);
		}
		else //if this is server, boardcast the signal
		{
			networkPtr->boardCast(packet);
		}
	}
    else if(eventObject->GetType() == "dialogue")
    {
        std::cout << eventObject->GetPropertyString("content") << std::endl;
    }
	else if (eventObject->GetType() == "battle")
	{
		std::cout << "Battle encountered." << std::endl;
        std::cout << "Name : " << eventObject->GetName() << std::endl;
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

	//reserve the vector to prevent reallocation
	//layerVector.reserve(8);

	auto playerLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Player";
	});

	if (playerLayer == layerVector.end())
		throw "not found!";

	//reserve the vector to prevent reallocation
	//playerLayer->objects.reserve(8);

	//create a map object representing player
    for(auto& pair: playerTree)
    {
        Player& player = pair.second;
        tmx::MapObject playerObj;
        playerObj.SetShapeType(tmx::MapObjectShape::Rectangle);
        playerObj.SetSize(sf::Vector2f(20, 12));
        playerObj.SetPosition(-50, -50);
        playerObj.AddPoint(sf::Vector2f());
        playerObj.AddPoint(sf::Vector2f(20, 0));
        playerObj.AddPoint(sf::Vector2f(20, 12));
        playerObj.AddPoint(sf::Vector2f(0, 12));
        playerObj.CreateDebugShape(sf::Color::Blue);
        playerObj.SetName(player.getName());
        
        playerLayer->objects.push_back(std::move(playerObj));
    }


	//push the map into the tree
	mapTree.emplace(filename, std::move(newMap));
}

void Gameplay::GameSystem::setReady(const std::string& playerName, const bool& newState)
{
	//get the target player
	Player& player = playerTree.at(playerName);
	player.setReady(newState);
}

void Gameplay::GameSystem::setPlayerPosition(const std::string & playerName, sf::Vector2f pos)
{
	Player& player = playerTree.at(playerName);
	player.setCharacterPosition(pos);
}

void Gameplay::GameSystem::interact()
{
    //ask player to "interect".
    tmx::MapObject* eventObj = thisPlayerPtr->interact();
    
    //if eventObj is not null, handle event.
    if(eventObj)
    {
        handleGameEvent(eventObj);
    }
}

void Gameplay::GameSystem::updateQuadTree()
{
	const sf::View& camera = interfacePtr->getCamera();
	sf::Vector2f position = camera.getCenter() - sf::Vector2f(camera.getSize().x / 2, camera.getSize().y / 2);
	sf::FloatRect cameraRect(position, camera.getSize());
	currentMap->UpdateQuadTree(cameraRect);
}

void Gameplay::GameSystem::createBattle( const std::string& initPlayerName, tmx::MapObject* battleObj)
{
    //get the Player from name
    Player& initPlayer = playerTree.at(initPlayerName);
    //get the position of player
    sf::Vector2f playerPos = initPlayer.getPosition();
    
    //let BattleFactory creates a battle
    //Battle battle(battleObj, playerPos);
    
    //set player into the battle
    //initPlayer.joinBattle(battle);
    
    //push the battle into the battleList
    //battleList.push_back(battle);
}
