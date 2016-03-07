#include <tmx/MapLoader.h>
#include "ResourcePath.h"
#include "ResourceManager.h"
#include "Game.h"
#include <TGUI/TGUI.hpp>

int main()
{
	sf::RenderWindow window{ { 800, 600 }, "Window" };
	tgui::Gui gui(window);

	tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>(resourcePath() +
		"Texture/Black.txt");

	tgui::Label::Ptr label = theme->load("label");
	label->setText("This is a label.");
	label->setPosition(10, 90);
	label->setTextSize(18);

	tgui::Font font(resourcePath() + "Texture/arial.ttf");
	label->setFont(font);
	gui.add(label);
	
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event); // Pass the event to the widgets
		}

		window.clear();
		gui.draw(); // Draw all widgets
		window.display();
	}
	/*
	Game game;
	game.start();
	return 0;
	*/

}