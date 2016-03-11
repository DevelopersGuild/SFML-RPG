#include "Configuration.h"

Configuration::Configuration() : 
	window(sf::VideoMode(1024, 768), "Game")
{
	window.setFramerateLimit(60);
}