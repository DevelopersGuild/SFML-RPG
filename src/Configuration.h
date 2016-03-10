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

	//resource Manager for sf::Texture
	ResourceManager<sf::Texture> texMan;

	//resource Manager for sf::Font
	ResourceManager<sf::Font> fontMan;

	//resource Manager for sf::Music
	ResourceManager<sf::Music> musMan;

	//the game window
	sf::RenderWindow window;

	//the cursor of the game
	//Cursor cursor

	//the volume of music
	int musicVolume;

	//the volume of sound effect
	int soundVolume;
};
#endif