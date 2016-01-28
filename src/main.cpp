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
    bound.setColor(sf::Color(255,102,102,255), sf::Color(255,102,102,255), sf::Color(255,51,51,255), sf::Color(255,51,51,255));
	//sf::Font font;
	//font.loadFromFile("..\\..\\Texture/arial.ttf");
    
	//TextBox textbox(font);
	//textbox.animateTo(sf::Vector2f(600, 600), sf::seconds(4), AnimationObject::Style::Decelerating);
    //textbox.setText("thisStringhasmorethantwentywordsohmygodthisisawesome!!");
    //textbox.setText("Test");
    //textbox.setText("this String has morrrre than twenty words!");
	//textbox.setText("hmf\tgwertya\nha\t lol\0 NULL lol!");		//sample text to be fixed...

	DragBound drag(sf::Vector2f(80, 80));


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
				//textbox.animateOpacityTo(180, sf::seconds(5));
				//textbox.animateTo(sf::Vector2f(20, 20), sf::seconds(5), AnimationObject::Style::Accelerating);
				
			}
			drag.processEvent(window,event);
		}
		
		//textbox.animateUpdate();
		bound.animateUpdate();
		bound.barAnimationUpdate();
		window.clear(sf::Color::White);
		window.draw(map);		//draw the map here
		window.draw(bound);
		window.draw(drag);
		//window.draw(textbox);
		window.display();
	}

	return 0;
}