#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include "Interface.h"
#include "ResourceManager.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "DGProject");
	window.setFramerateLimit(60);
    
    ResourceManager resMan;
    resMan.add("Texture/cursor_test.png");
    Cursor cursor(window);
    cursor.loadTexture(resMan.get("Texture/cursor_test.png"));
    window.setMouseCursorVisible(false);

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
            cursor.processEvent(window, event);
		}
		
		window.clear(sf::Color::White);
		window.draw(map);		//draw the map here
        window.draw(cursor);
		//window.draw(textbox);
		window.display();
	}

	return 0;
}