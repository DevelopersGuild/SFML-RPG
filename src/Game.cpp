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
    
    config.resMan.add("Texture/Start.png");
    config.resMan.add("Texture/Start_2.png");
    
    sf::RectangleShape testing;
    testing.setSize(sf::Vector2f(260,90));
    testing.setPosition(sf::Vector2f(1000,200));
    testing.setTexture(&config.resMan.get("Texture/Start.png"));
    
	//debug
    
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
            
            if(sf::Mouse::getPosition(window).x > 1000 && sf::Mouse::getPosition(window).x < 1260
               && sf::Mouse::getPosition(window).y > 200 && sf::Mouse::getPosition(window).y < 290)
                testing.setTexture(&config.resMan.get("Texture/Start_2.png"));
            else
            {
                testing.setTexture(&config.resMan.get("Texture/Start.png"));
            }
		}
        
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