#include "Game.h"

Game::Game() : 
window(sf::VideoMode(1440, 900), "Game")
{
	states = GAME_STATES::Menu;
	window.setFramerateLimit(60);
}

void Game::start() 
{
	//debug
	config.resMan.add("Texture/Tower1.png");
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(1440, 900));
	rect.setTexture(&config.resMan.get("Texture/Tower1.png"));
    
    config.resMan.add("Texture/Start1.png");
    config.resMan.add("Texture/Start2.png");
    
	Button testing(&config.resMan.get("Texture/Start1.png"), &config.resMan.get("Texture/Start2.png"));
	testing.setSize(sf::Vector2f(260, 90));
	testing.setPosition(sf::Vector2f(1000, 200));
	testing.animateOpacityTo(0, sf::seconds(0));

	//debug
    
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		testing.animateUpdate();
		testing.processEvent(window, event);
		window.clear();
        window.draw(rect);
		window.draw(testing);
		window.display();
	}
}

/*
note:
the button size in the menu is 260x90
*/