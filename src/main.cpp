#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "DGProject");

#ifdef _MSC_VER	//if Visual Studio
	tmx::MapLoader map("..\\..\\maps\\");
#endif
#ifdef __MACH__	//if Mac
	tmx::MapLoader map(resourcePath() + "maps/");
#endif

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
		window.draw(map);
		window.display();
	}

	return 0;
}