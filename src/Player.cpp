#include "Player.h"
using namespace Gameplay;

Player::Player(Configuration& config)
{
	name = "Unnamed player";
	charPtr.reset(new Character(config));
}

Player::Player(Configuration& config, const std::string& playerName, const std::string& charName)
{
	name = playerName;
	charPtr.reset(new Character(config, charName));
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*charPtr);
}

void Gameplay::Player::changeMap(tmx::MapLoader * map, const std::string locationName)
{
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
    
	charPtr->setCharPtr(&(*playerObj));

	//move the player to event position
    sf::Vector2f eventPosition = eventObj->GetPosition();
	charPtr->setPosition(eventPosition);
}

void Player::moveCharacter(const Character::Direction& direction)
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
	for (tmx::MapObject& obj : objLayer->objects)
	{
		if (charRect.intersects(obj.GetAABB()))
			collided = true;
	}

	//5.if no collision, move the player
	if (!collided)
	{
		charPtr->move(direction);
	}	

	//6.perform the event check
	//...TBD
}