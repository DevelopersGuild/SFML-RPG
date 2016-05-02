#ifndef CHARACTER_H
#define CHARACTER_H
#include "Item.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "tmx/MapLoader.h"
#include "Configuration.h"

namespace Gameplay
{
	class Character : public sf::Drawable
	{
	private:
		//for accessing resourse
		Configuration& config;

		//the name of the character(not player)
		std::string name;

		//Character's HP
		int hp;

		//Character's Attack
		int atk;

		//Character's Defense
		int def;

		//Character's Speed
		int speed;

		//the direction that the character is looking at
		enum Direction{up, down, left, right} direction;

		//character's sprite
		sf::Sprite sprite;

	public:
		Character(Configuration& newConfig) : config(newConfig)
		{
			name = "Unnamed character";
			hp = 100;
			atk = 1;
			def = 1;
			speed = 10;

			sprite.setTexture(config.texMan.get("Actor4.png"));
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			sprite.setPosition(200, 200);
		}

		Character(Configuration& newConfig, const std::string& newName) : 
			Character(newConfig)
		{
			name = newName;
		}

		void move(const float& x, const float& y)
		{
			sprite.move(x, y);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(sprite);
		}
	};
}
#endif