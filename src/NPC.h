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
		sf::Sprite	sprite;
		SpriteList upList;
		SpriteList rightList;
		SpriteList downList;
		SpriteList leftList;
		bool talkable;
		std::string dialogue_content;
		DIRECTION direction;
		tmx::MapLoader* currentMap;
	public:
		NPC() = delete;
		NPC(const NPC&) = delete;
		NPC& operator=(const NPC&) = delete;
		NPC(tmx::MapLoader* map, sf::Texture& texture, const std::string& name, bool talkable);

		const std::string& getName() { return name; }
		void setDirection(DIRECTION direction);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool isTalkable() { return talkable; }
		void setDialogue(const std::string& dialogue) { dialogue_content = dialogue; }
		const std::string& getDialogue() { return dialogue_content; }
		tmx::MapLoader* getMap() { return currentMap; }

		virtual void interact() { ; }
		virtual void addToSpriteList(sf::IntRect intRect, const DIRECTION& direction);
	};
}