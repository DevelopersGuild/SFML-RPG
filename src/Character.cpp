#include "Character.h"
using namespace Gameplay;

Character::Character(Configuration& newConfig) : config(newConfig)
{
	mapCharPtr = nullptr;

	name = "Unnamed character";
	max_hp = 100;
	hp = max_hp;
	atk = 5;
	def = 5;
	speed = 3;
    speed_battle = 6;
	level = 1;
    current_exp = 0;
    exp_cap = 20;
	direction = down;
	sprite_UpdateRate = 0.08f;
	distance_since_lastBattle = 0;
    num_Continuous_battle_escape = 0;

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
    sprite.setOrigin(16, 16);
    
    nameText.setString(name);
    nameText.setFont(config.fontMan.get("Carlito-Regular.ttf"));
    nameText.setCharacterSize(10);
    nameText.setColor(sf::Color::Black);
}

Character::Character(Configuration& newConfig, const std::string& newName) : Character(newConfig)
{
	name = newName;
    nameText.setString(name);
}

void Character::move(const Direction& newDirection)
{
	//if the pointer to character on the map is null, do nothing.
	if (mapCharPtr)
	{
		//move according the direction.
		switch (newDirection)
		{
		case Direction::left:
			sprite.move(-speed, 0);
			mapCharPtr->Move(-speed, 0);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(leftList.getNext());
				spriteClock.restart();
			}
			direction = Direction::left;
			break;
		case Direction::right:
			sprite.move(speed, 0);
			mapCharPtr->Move(speed, 0);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(rightList.getNext());
				spriteClock.restart();
			}
			direction = Direction::right;
			break;
		case Direction::up:
			sprite.move(0, -speed);
			mapCharPtr->Move(0, -speed);
			if (direction != newDirection || spriteClock.getElapsedTime() > sf::seconds(sprite_UpdateRate))
			{
				sprite.setTextureRect(upList.getNext());
				spriteClock.restart();
			}
			direction = Direction::up;
			break;
		case Direction::down:
			sprite.move(0, speed);
			mapCharPtr->Move(0, speed);
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
        //set the position of player's name on the character's head
        nameText.setPosition(sprite.getPosition() - sf::Vector2f(0, 27));

		//increse the distance_since_lastBattle(increase the change of battle encounter)
		distance_since_lastBattle += speed;
	}

}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
    target.draw(nameText);
}

void Gameplay::Character::setPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
	mapCharPtr->SetPosition(position + sf::Vector2f(-10, 4));
    //set the position of player's name on the character's head
    sf::FloatRect bound = nameText.getGlobalBounds();
    nameText.setOrigin(bound.width / 2, bound.height / 2);
    //set the position of player's name on the character's head
    nameText.setPosition(sprite.getPosition() - sf::Vector2f(0, 27));
}

sf::FloatRect Gameplay::Character::getAABB()
{
	return mapCharPtr->GetAABB();
}

sf::FloatRect Gameplay::Character::getDectionArea()
{
	return sf::FloatRect(sprite.getPosition() - sf::Vector2f(16, 16), sf::Vector2f(32, 32));
}

void Gameplay::Character::setDirection(Direction newDirection)
{
    direction = newDirection;
    switch(newDirection)
    {
        case Direction::left:
            sprite.setTextureRect(leftList.front());
            break;
        case Direction::right:
            sprite.setTextureRect(rightList.front());
            break;
        case Direction::up:
            sprite.setTextureRect(upList.front());
            break;
        case Direction::down:
            sprite.setTextureRect(downList.front());
            break;
        default:
            ;
    }
}

void Gameplay::Character::setMaxHp(const int &value)
{
    max_hp = value;
    if(max_hp < hp)
    {
        hp = max_hp;
    }
}

void Gameplay::Character::setCurrentHp(const int &value)
{
    hp = value;
    if(max_hp < hp)
    {
        hp = max_hp;
    }
}

void Gameplay::Character::gainExp(int value)
{
	current_exp += value;

	while(current_exp >= exp_cap)
	{
		current_exp -= exp_cap;
		levelUp();
	}
}

void Gameplay::Character::levelUp()
{
	// TODO: test function when battle is done
	// Update attributes
	level++;
	max_hp += 0;
	atk += 0;
	def += 0;
	speed += 0;

	// Update the exp_cap
	exp_cap += 0;
}