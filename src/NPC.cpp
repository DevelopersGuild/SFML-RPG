#include "NPC.h"

using namespace Gameplay;

Gameplay::NPC::NPC(sf::Font & font, sf::Texture & spriteTexture, tmx::MapLoader * map, const std::string & name)
{
	text_name.setFont(font);
	text_name.setCharacterSize(10);
	text_name.setColor(sf::Color::Black);
	sprite.setTexture(spriteTexture);
	currentMap = map;
	this->name = name;
	text_name.setString(name);
}

void Gameplay::NPC::setSpriteRect(const sf::IntRect & upRect, const sf::IntRect & rightRect, const sf::IntRect & downRect, const sf::IntRect & leftRect)
{
	this->upRect = upRect;
	this->rightRect = rightRect;
	this->downRect = downRect;
	this->leftRect = leftRect;
}

void Gameplay::NPC::setDirection(DIRECTION direction)
{
	this->direction = direction;
	switch (direction)
	{
	case up:
		sprite.setTextureRect(upRect);
		break;
	case right:
		sprite.setTextureRect(rightRect);
		break;
	case down:
		sprite.setTextureRect(downRect);
		break;
	case left:
		sprite.setTextureRect(leftRect);
		break;
	default:
		;
	}
}

void Gameplay::NPC::setPosition(const sf::Vector2f & pos)
{
	sprite.setPosition(pos);
	//set the position of NPC's name on the character's head
	sf::FloatRect bound = text_name.getGlobalBounds();
	text_name.setOrigin(bound.width / 2, bound.height / 2);
	//set the position of NPC's name on the character's head
	text_name.setPosition(sprite.getPosition() - sf::Vector2f(-16, 15));
}

void Gameplay::NPC::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(text_name);
}
