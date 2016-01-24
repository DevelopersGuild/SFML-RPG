#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include "Interface.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "DGProject");
	window.setFramerateLimit(60);

	Bar bound;
	bound.setSize(sf::Vector2f(600, 50));
	bound.setBarAnimation(0.2);
	bound.animateOpacityTo(100, sf::seconds(5));
	bound.animateTo(sf::Vector2f(0, 500), sf::seconds(5), AnimationObject::Style::Regularly);

	//set MapLoader to open the "map" folder
	//we will add a resource manager later
#ifdef __MACH__	//if Mac
	tmx::MapLoader map(resourcePath() + "maps/");
#endif
#ifdef _MSC_VER	//if Visual Studio
	tmx::MapLoader map("..\\..\\maps\\");
#endif
	//load the map here, currently the map name is "test.tmx"
	map.Load("test.tmx");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				bound.animateOpacityTo(255, sf::seconds(0.5));
				bound.setBarAnimation(1);
			}
				
		}
		bound.animateUpdate();
		bound.barAnimationUpdate();
		window.clear(sf::Color::White);
		window.draw(map);		//draw the map here
		window.draw(bound);
		window.display();
	}

	return 0;
}