#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
namespace Gameplay
{
	/*
	NPC (non playable character) class
	handles the npc in the game.
	NPCs have their own sprite and spriteList. They can talk. They can even help trigger event(TBD)
	*/
	class NPC : public sf::Drawable
	{
	public:
		enum DIRECTION{up, right, down, left};
	private:
		std::string name;
		sf::Text text_name;
		DIRECTION direction;
		sf::Sprite sprite;
		sf::IntRect upRect;
		sf::IntRect rightRect;
		sf::IntRect downRect;
		sf::IntRect leftRect;
		tmx::MapLoader* currentMap;
	public:
		NPC() = delete;
		NPC(const NPC&) = delete;
		NPC& operator=(const NPC&) = delete;
		NPC(sf::Font& font, sf::Texture& spriteTexture, tmx::MapLoader* map, const std::string& name);

		std::string getName() { return name; }
		void setSpriteRect(const sf::IntRect& upRect, const sf::IntRect& rightRect, const sf::IntRect& downRect, const sf::IntRect& leftRect);
		void setDirection(DIRECTION direction);
		const tmx::MapLoader* getMap() { return currentMap; }
		void setPosition(const sf::Vector2f& pos);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}