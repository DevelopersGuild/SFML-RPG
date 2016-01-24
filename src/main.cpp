#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include "Interface.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "DGProject");
	window.setFramerateLimit(60);

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
		}
		window.clear(sf::Color::White);
		//window.draw(map);		//draw the map here
		window.display();
	}

	return 0;
}