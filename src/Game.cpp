#include "Game.h"

Game::Game() : 
window(sf::VideoMode(1440, 990), "Game")
{
	states = GAME_STATES::preGame;
	window.setFramerateLimit(60);
}

void Game::start() 
{
	//debug
	config.resMan.add("Texture/Tower1.png");
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(1440, 990));
	rect.setTexture(&config.resMan.get("Texture/Tower1.png"));
	//debug

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(rect);	//debug
		window.display();
	}
}

/*
mote:
the button size in the menu is 260x90
*/