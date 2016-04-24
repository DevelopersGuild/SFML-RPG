#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ResourceManager.h"
#include "Cursor.h"
#include <TGUI/TGUI.hpp>

/*
Configuration class
stores game resources and basic info.
known issue: do not create std::string here!
*/
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

	//resource Manager for sf::sound
	ResourceManager<sf::Sound> soundMan;

	//the game window
	sf::RenderWindow window;

	//the cursor of the game
	Cursor cursor;

	//Account's name(player's name)
	std::string player_name;
};
#endif