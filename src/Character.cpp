#include "Character.h"
using namespace Gameplay;

tmx::MapObject* Gameplay::Character::findThisCharacter()
{
	//get the the "Player" layer of the map
	std::vector<tmx::MapLayer>::iterator playerLayer = find_if(mapCharPtr->begin(), mapCharPtr->end(), [&](tmx::MapLayer& layer)
	{
		return layer.name == "Player";
	});

	//get the object vector from player layer
	std::vector<tmx::MapObject>& playerVector = playerLayer->objects;

	//find the target player
	for (tmx::MapObject& player : playerVector)
	{
		if (player.GetName() == name)
			return &player;
	}

	//player not found, throw exception
	throw "player not found!";
}

Character::Character(Configuration& newConfig) : config(newConfig)
{
	mapCharPtr = nullptr;

	name = "Unnamed character";
	hp = 100;
	atk = 1;
	def = 1;
	speed = 3;
	direction = down;
	sprite_UpdateRate = 0.08f;

	//initialize the spriteLists
	for (int i = 0; i < 3; i++)
	{
		downList.add(sf::IntRect(i * 32, 0, 32, 32));
		leftList.add(sf::IntRect(i * 32, 32, 32, 32));
		rightList.add(sf::IntRect(i * 32, 64, 32, 32));
		upList.add(sf::IntRect(i * 32, 96, 32, 32));
	}

	sprite.setTexture(config.texMan.get("Actor4.png"));
	sprite.setTextureRect(downList.getNext());
}

Character::Character(Configuration& newConfig, const std::string& newName) : Character(newConfig)
{
	name = newName;
}

void Character::move(const Direction& newDirection)
{
	tmx::MapObject* thisPlayer = findThisCharacter();
	if (!thisPlayer)
	{
		throw "Player not found!";
	}
	//if the pointer to character on the map is null, do nothing.
	if (mapCharPtr)
	{
		//move according the direction.
		switch (newDirection)
		{
		case Direction::left:
			sprite.move(-speed, 0);
			thisPlayer->Move(-speed, 0);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(leftList.getNext());
				spriteClock.restart();
			}
			direction = Direction::left;
			break;
		case Direction::right:
			sprite.move(speed, 0);
			thisPlayer->Move(speed, 0);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(rightList.getNext());
				spriteClock.restart();
			}
			direction = Direction::right;
			break;
		case Direction::up:
			sprite.move(0, -speed);
			thisPlayer->Move(0, -speed);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(upList.getNext());
				spriteClock.restart();
			}
			direction = Direction::up;
			break;
		case Direction::down:
			sprite.move(0, speed);
			thisPlayer->Move(0, speed);	
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(downList.getNext());
				spriteClock.restart();
			}
			direction = Direction::down;
			break;
		default:
			;
		}
	}

}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Gameplay::Character::setPosition(sf::Vector2f & position)
{
	sprite.setPosition(position);

	tmx::MapObject* thisPlayer = findThisCharacter();
	if (thisPlayer)
		thisPlayer->SetPosition(position + sf::Vector2f(6, 20));
}

sf::FloatRect Gameplay::Character::getAABB()
{
	tmx::MapObject* thisPlayer= findThisCharacter();
	if (thisPlayer)
		return thisPlayer->GetAABB();
	else
		throw "Player not found!";
}
