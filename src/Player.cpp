#include "Player.h"
using namespace Gameplay;

Player::Player(Configuration& config)
{
	name = "Unnamed player";
	currentMap = nullptr;
	charPtr.reset(new Character(config));
}

Player::Player(Configuration& config, const std::string& playerName, const std::string& charName)
{
	name = playerName;
	currentMap = nullptr;
	charPtr.reset(new Character(config, charName));
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*charPtr);
}

void Gameplay::Player::changeMap(tmx::MapLoader * map, const std::string locationName)
{
	//if the character is already in another map, put the character at invisible place(-50,-50)
	if (currentMap != nullptr)
	{
		charPtr->setPosition(sf::Vector2f(-50,-50));
	}
	//change pointer to the new map
	currentMap = map;

	//set the character pointer to the characterObj of this map
	//look for the event layer
	auto layerVector = currentMap->GetLayers();
	auto eventLayer = find_if(layerVector.begin(), layerVector.end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Event";
	});

	if (eventLayer == layerVector.end())
		throw "not found!";	//TBD

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

	if (playerLayer == layerVector.end())
		throw "not found!";

	//look for the target player
	auto playerObj = find_if(playerLayer->objects.begin(), playerLayer->objects.end(), [&](tmx::MapObject& obj) {
		return name == obj.GetName();
	});

	if (playerObj == playerLayer->objects.end())
		throw "not found!";

	//set the charPtr
    
	charPtr->setCharLayer(&currentMap->GetLayers());

	//move the player to event position
    sf::Vector2f eventPosition = eventObj->GetPosition();
	charPtr->setPosition(eventPosition);
}

tmx::MapObject* Player::moveCharacter(const Character::Direction& direction)
{
	//collision Test
	//1.create a temporary float rect from player's rect
	sf::FloatRect charRect = charPtr->getAABB();

	//2.shift the temmporary rect to the direction
	//get the speed of the player
	float speed = charPtr->getSpeed();

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

	//3.get the object layer of the current map, will use tmx's tree later
	auto& layer = currentMap->GetLayers();
	
	auto objLayer = find_if(layer.begin(), layer.end(), [&](tmx::MapLayer& mapLayer) {
		return mapLayer.name == "Objects";
	});

	if (objLayer == layer.end())
		throw "not found!";

	//4.for each map obj check if there is intersection
	//assume no collided
	bool collided = false;
	std::vector<tmx::MapObject*> objVector = currentMap->QueryQuadTree(charPtr->getDectionArea());
	for (tmx::MapObject* obj : objVector)
	{
		if (obj->GetParent() == "Objects" && charRect.intersects(obj->GetAABB()))
			collided = true;
	}

	//5.if no collision, move the player. if collision, just change the direction
	if (!collided)
		charPtr->move(direction);
    else
        charPtr->setDirection(direction);

	//6.perform the event check
	//go to event layer
	auto eventLayer = find_if(layer.begin(), layer.end(), [&](tmx::MapLayer& mapLayer) {
		return mapLayer.name == "Event";
	});

	if (eventLayer == layer.end())
		throw "not found!";
	
	//if the player collides with any event object, return that object
	auto eventObject = find_if(eventLayer->objects.begin(), eventLayer->objects.end(), [&](tmx::MapObject& obj) {
		return obj.GetAABB().intersects(charPtr->getAABB());
	});
	
	//7.return mapObjects pointer
	//if not found, return nullptr. If found, return pointer to mapObject
	if (eventObject == eventLayer->objects.end())
		return nullptr;
	else
		return &(*eventObject);
}

tmx::MapObject* Gameplay::Player::interact()
{
    tmx::MapObject* temp = nullptr;
    Character::Direction direction = charPtr->getDirection();
    
    //1.create a temporary float rect from player's rect
    sf::FloatRect charRect = charPtr->getAABB();
    
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
    
    if (eventLayer == layer.end())
        throw "not found!";
    
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