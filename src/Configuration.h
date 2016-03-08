#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ResourceManager.h"
#include <TGUI/TGUI.hpp>

class Configuration
{
private:

public:
	Configuration();
	Configuration(const Configuration&) = delete;
	Configuration operator=(const Configuration&) = delete;

	//resource Manager for texture
	tgui::TextureManager texMan;

	//the game window
	sf::RenderWindow window;

	//the cursor of the game
	//Cursor cursor
};
#endif