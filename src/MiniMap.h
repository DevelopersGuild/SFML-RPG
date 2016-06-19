#pragma once

#include "GameSystem.h"
#include "Configuration.h"

namespace Gameplay
{
	/*
	MiniMap class
	handles mini map graphics in the game.
	*/
	class MiniMap
	{
	private:
		Configuration& config;
		tgui::Panel::Ptr panel;
		tgui::Picture::Ptr minimapPic;
		tgui::Picture::Ptr pin;
		tmx::MapLoader* currentMap;
	public:
		MiniMap(Configuration& config);
		void update(const sf::Vector2f playerPosition, tmx::MapLoader* map);
		void addToGui(tgui::Gui& gui);
		void show();
		void hide();
		bool isDisplaying() { return panel->isVisible(); }
	};
}