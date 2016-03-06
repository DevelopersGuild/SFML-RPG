#include "Game.h"

Game::Game() : 
window(sf::VideoMode(1440, 900), "Game")
{
	states = GAME_STATES::Menu;
	window.setFramerateLimit(60);
}

void Game::start() 
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
}
