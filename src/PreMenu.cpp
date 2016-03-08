#include "PreMenu.h"

PreMenu::PreMenu(Configuration & newConfig) :
	config(newConfig)
{

}

bool PreMenu::initialize()
{

	return true;
}

void PreMenu::run()
{
	sf::RenderWindow& window = config.window;

	tgui::Gui gui(window);
	tgui::Label::Ptr label = std::make_shared<tgui::Label>();
	label->setText("Hello world!");
	label->setTextColor(tgui::Color(255, 255, 255, 255));
	label->setPosition(100, 100);
	gui.add(label);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		gui.draw();
		window.display();
	}
}
