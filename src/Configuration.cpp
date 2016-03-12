#include "Configuration.h"

Configuration::Configuration() : 
	window(sf::VideoMode(1024, 768), "Game"),
	cursor(window)
{
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
}