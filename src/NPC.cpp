#include "NPC.h"

using namespace Gameplay;

Gameplay::NPC::NPC(tmx::MapLoader* map, sf::Texture& texture, const std::string& name, bool talkable)
{
	currentMap = map;
	this->name = name;
	direction = down;
	sprite.setTexture(texture);
	sprite.setOrigin(16, 16);
	this->talkable = talkable;
}

void Gameplay::NPC::setDirection(DIRECTION direction)
{
	this->direction = direction;
	switch (direction)
	{
	case DIRECTION::left:
		sprite.setTextureRect(leftList.getNext());
		break;
	case DIRECTION::right:
		sprite.setTextureRect(rightList.getNext());
		break;
	case DIRECTION::up:
		sprite.setTextureRect(upList.getNext());
		break;
	case DIRECTION::down:
		sprite.setTextureRect(downList.getNext());
		break;
	}
}

void Gameplay::NPC::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Gameplay::NPC::addToSpriteList(sf::IntRect intRect, const DIRECTION & newDirection)
{
	switch (newDirection)
	{
	case DIRECTION::left:
		leftList.add(intRect);
		break;
	case DIRECTION::right:
		rightList.add(intRect);
		break;
	case DIRECTION::up:
		upList.add(intRect);
		break;
	case DIRECTION::down:
		downList.add(intRect);
		break;
	default:
		;
	}
}
