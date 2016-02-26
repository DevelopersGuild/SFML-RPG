#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include "Interface.h"
#include "ResourceManager.h"
#include <iostream>
#include "Game.h"

int main()
{
	//sf::RenderWindow window(sf::VideoMode(640, 640), "DGProject");
	Game game;
	game.start();
	return 0;
}