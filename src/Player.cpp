#include "Player.h"
#include <sstream>

using namespace Gameplay;

Player::Player(Configuration& newConfig) :
    config(newConfig),
    character(config)
{
	name = "Unnamed player";
	currentMap = nullptr;
	ready = false;
    state = normal;
}

Player::Player(Configuration& newConfig, const std::string& playerName, const std::string& charName) :
    config(newConfig),
    name(playerName),
    character(config, charName)
{
	currentMap = nullptr;
	ready = false;
    state = normal;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(character);
}

void Gameplay::Player::changeMap(tmx::MapLoader * map, const std::string locationName)
{
	//if the character is already in another map, put the character at invisible place(-50,-50)
	if (currentMap != nullptr)
	{
		character.setPosition(sf::Vector2f(-50,-50));
	}
	//change pointer to the new map
	currentMap = map;

	//set the character pointer to the characterObj of this map
	//look for the event layer
	auto& layerVector = currentMap->GetLayers();
	auto eventLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Event";
	});

	assert (eventLayer != layerVector.end());

	//look for the target obj
	auto eventObj = find_if(eventLayer->objects.begin(), eventLayer->objects.end(), [&](tmx::MapObject& obj) {
		return obj.GetName() == locationName;
	});

	if (eventObj == eventLayer->objects.end())
		throw "not found!";	//TBD

	//look for the player layer
	auto playerLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Player";
	});

	assert (playerLayer != layerVector.end());

	//look for the target player
	auto playerObj = find_if(playerLayer->objects.begin(), playerLayer->objects.end(), [&](tmx::MapObject& obj) {
		return name == obj.GetName();
	});

	assert(playerObj != playerLayer->objects.end());

	//set the charPtr
	character.setCharLayer(&(*playerObj));

	//move the player to event position
    sf::Vector2f eventPosition = eventObj->GetPosition();
	character.setPosition(eventPosition);

	//if this map is safe, record to the lastSafePlace
	if (map->GetPropertyString("battle") == "false")
	{
		lastSafePlace.lastSafeMap = map;
		lastSafePlace.lastSafePosition = locationName;
	}
}

tmx::MapObject* Player::moveCharacter(tmx::MapLoader* cameraMap, const Character::Direction& direction)
{
	//if character is not on the cameraMap, do not perform collision Test
	if (cameraMap != currentMap)
	{
		character.move(direction);
		return nullptr;
	}

	//collision Test
	//1.create a temporary float rect from player's rect
	sf::FloatRect charRect = character.getAABB();

	//2.shift the temmporary rect to the direction
	//get the speed of the player
	float speed = character.getSpeed();

	//shift according to the direction
	switch (direction)
	{
	case Character::Direction::up:
		charRect.top -= speed;
		break;
	case Character::Direction::down:
		charRect.top += speed;
		break;
	case Character::Direction::left:
		charRect.left -= speed;
		break;
	case Character::Direction::right:
		charRect.left += speed;
		break;
	default:
		;
	}

	auto& layer = currentMap->GetLayers();

	//3.get object Layer
	const auto& objLayer = find_if(layer.begin(), layer.end(), [&](tmx::MapLayer& mapLayer) {
		return mapLayer.name == "Objects";
	});

	assert(objLayer != layer.end()); //if not found, terminate the program

	//4.for each map obj check if there is intersection, perform collision test if the current map is same as character's map
	//assume no collided
	bool collided = false;

	const std::vector<tmx::MapObject*>& objVector = currentMap->QueryQuadTree(character.getDectionArea());
		
	for (tmx::MapObject* obj : objVector)
	{
		if (obj->GetParent() == "Objects" && charRect.intersects(obj->GetAABB()))
		{
			collided = true;	//collision found, stop further searching
			break;
		}		
	}
	
	//5.if no collision, move the player. if collision, just change the direction
	if (!collided)
		character.move(direction);
    else
        character.setDirection(direction);

	//6.perform the event check
	//go to event layer
	const auto& eventLayer = find_if(layer.begin(), layer.end(), [&](tmx::MapLayer& mapLayer) {
		return mapLayer.name == "Event";
	});
	
	//if the player collides with any event object, return that object
	auto eventObject = find_if(eventLayer->objects.begin(), eventLayer->objects.end(), [&](tmx::MapObject& obj) {
		return obj.GetAABB().intersects(character.getAABB());
	});

	//7.return mapObjects pointer
	//if not found, proceed battle check. If found, return pointer to mapObject
	if (eventObject == eventLayer->objects.end())
	{
		//if need battle, return the event_battle object in the map. Return nullptr else.
		if (isBattleEncounter())
		{
            character.setDistance_lastBattle(0);	//test, should be in joinBattle() function.
            
            auto battleLayer = find_if(currentMap->GetLayers().begin(), currentMap->GetLayers().end(),[&](tmx::MapLayer& layer){
                return layer.name == "Battle";
            });
            
            //try to find the battlezone that player located
            for(auto it = battleLayer->objects.begin(); it != battleLayer->objects.end(); it++)
            {
                //if player is in that battlezone, return that battle Object
                if(it->GetAABB().contains(getPosition()))
                {
                    return &(*it);
                }
            }

            //if not belong to any battlezone, return global battle object
            auto globalBattleObj = find_if(battleLayer->objects.begin(), battleLayer->objects.end(), [&](tmx::MapObject& obj){
                return obj.GetName() == "event_battle";
            });
            
			assert(globalBattleObj != battleLayer->objects.end()); //terminate if no battle object is found.(need battle, but no battle obj found.)
			return &(*globalBattleObj);
		}
		else
			return nullptr;
	}
	else
		return &(*eventObject);
}

tmx::MapObject* Gameplay::Player::interact()
{
    tmx::MapObject* temp = nullptr;
    Character::Direction direction = character.getDirection();
    
    //1.create a temporary float rect from player's rect
    sf::FloatRect charRect = character.getAABB();
    
    //2.slightly move the charRect along the character's direction
    switch (direction)
    {
        case Character::Direction::up:
            charRect.top -= 5;
            break;
        case Character::Direction::down:
            charRect.top += 5;
            break;
        case Character::Direction::left:
            charRect.left -= 5;
            break;
        case Character::Direction::right:
            charRect.left += 5;
            break;
        default:
            ;
    }
    
    //3.perform event check
    //go to event layer
    auto& layer = currentMap->GetLayers();
    auto eventLayer = find_if(layer.begin(), layer.end(), [&](tmx::MapLayer& mapLayer) {
        return mapLayer.name == "Event";
    });

	assert(eventLayer != layer.end());
    
    //if the player collides with any event object, return that object
    auto eventObject = find_if(eventLayer->objects.begin(), eventLayer->objects.end(), [&](tmx::MapObject& obj) {
        return obj.GetAABB().intersects(charRect);
    });
    
    //4.if found, set the pointer to that object
    if(eventObject != eventLayer->objects.end())
    {
        temp = &(*eventObject);
    }
    
    return temp;
}

bool Gameplay::Player::isBattleEncounter()
{
	//if the map is safe(town, house, etc...), then "battle" will be false, then skip this
	if (currentMap->GetPropertyString("battle") == "true")
	{
		//get the rate of battle of this map
		std::stringstream ss;
		ss << currentMap->GetPropertyString("battle_rate");
		int battle_rate;
		ss >> battle_rate;

		//TBD, Sabrina's part
		if (character.getDistance_lastBattle() / 8 > battle_rate)
			return true;
	}
	return false;
}

void Gameplay::Player::joinBattle(std::shared_ptr<Battle> battle)
{
    battlePtr = battle;
	state = STATE::inBattle;
    std::unique_ptr<BattleCharacter> battlePlayer(new BattlePlayer(character));
    battlePlayer->loadSprite(config.texMan.get("playerSprite.png"));
    battle->addCharacter(std::move(battlePlayer));
    battle->setCharPosition(name, 200);
}

void Gameplay::Player::leaveBattle()
{
    battlePtr.reset();
	state = STATE::normal;
}

void Gameplay::Player::teleport_ToLastSafeLocation()
{
	changeMap(lastSafePlace.lastSafeMap, lastSafePlace.lastSafePosition);
}
