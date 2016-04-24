#include "Configuration.h"

Configuration::Configuration() : 
	window(sf::VideoMode(1024, 768), "Game", sf::Style::Close),
	cursor(window)
{
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
}