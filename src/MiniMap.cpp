#include "MiniMap.h"

Gameplay::MiniMap::MiniMap(Configuration & newConfig) : config(newConfig)
{
	const sf::Vector2u& windowSize = config.window.getSize();
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(windowSize.x * 0.30, windowSize.y * 0.30);
	panel->setPosition(windowSize.x * 0.70, 0);
	panel->setOpacity(0.5);

	minimapPic = std::make_shared<tgui::Picture>();
	minimapPic->setSize(panel->getSize());
	minimapPic->setPosition(0, 0);
	panel->add(minimapPic);

	pin = std::make_shared<tgui::Picture>();
	pin->setSize(30, 30);
	pin->setPosition(0, 0);
	pin->setTexture(config.texMan.get("miniPin.png"));
	panel->add(pin);
    panel->hide();
	currentMap = nullptr;
}

void Gameplay::MiniMap::update(const sf::Vector2f playerPosition, tmx::MapLoader * map)
{
	//if the map has changed, reload the miniMap png
	if (currentMap != map)
	{
		currentMap = map;
		std::string miniMapFile = currentMap->GetPropertyString("miniMap");	//get the mini map file name
		if (miniMapFile != "")
		{
			minimapPic->setTexture(config.texMan.get(miniMapFile));	//get the file from texture manager
			show();
		}			
		else
			hide();	
	}
	//peter's part: scale the player's position to minimap's pin
	float y_portion = playerPosition.y / map->GetMapSize().y;
	float x_portion = playerPosition.x / map->GetMapSize().x;

	pin->setPosition(minimapPic->getSize().x * x_portion, minimapPic->getSize().y * y_portion);
}

void Gameplay::MiniMap::addToGui(tgui::Gui & gui)
{
	gui.add(panel);
}

void Gameplay::MiniMap::show()
{
	panel->show();
}

void Gameplay::MiniMap::hide()
{
	panel->hide();
}
