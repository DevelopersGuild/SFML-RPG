#include "PreMenu.h"
#include "ResourcePath.h"
#include <iostream>

PreMenu::PreMenu(Configuration & newConfig) :
	config(newConfig),
	finished(false)
{

}

void PreMenu::run()
{
	sf::RenderWindow& window(config.window);

	//the background when loading
	sf::RectangleShape backgrd;
	backgrd.setSize(sf::Vector2f(1024, 768));
	backgrd.setTexture(&config.texMan.get("Tower1.png"));

	//the gui in loading
	tgui::Gui gui(window);
	tgui::Label::Ptr label = std::make_shared<tgui::Label>();
	
	//the "loading" label in loading
	label->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	label->setText("Loading...");
	label->setTextColor(tgui::Color(0, 0, 0, 255));
	label->setPosition(900, 700);
	gui.add(label);

	//start the initialze thread
	std::thread init(&PreMenu::initialize, this);
	
	//when not finished, poll event
	while (window.isOpen() && !finished)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();	//to be changed, the init thread still running
			}
		}

		window.clear();
		window.draw(backgrd);
		gui.draw();
		window.display();
	}
	init.join();
}

void PreMenu::initialize()
{
	sf::Music& test = config.musMan.get("Theme1.ogg");	
	std::this_thread::sleep_for(std::chrono::seconds(2));	//TBC, test only

	finished = true;
}