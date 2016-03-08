#include "Menu.h"

Menu::Menu(Configuration & newConfig) :
	config(newConfig)
{

}

void Menu::run()
{
	sf::RenderWindow& window(config.window);

	sf::Music& bgMusic = config.musMan.get("Music/Theme1.ogg");
	bgMusic.play();

	//debug
	sf::RectangleShape backgrd;
	backgrd.setSize(sf::Vector2f(1024, 768));
	backgrd.setTexture(&config.texMan.get("Texture/Tower1.png"));

	tgui::Gui gui(window);

	tgui::Button::Ptr exitButton = std::make_shared<tgui::Button>();
	exitButton->setPosition(800, 700);
	exitButton->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	exitButton->setText(sf::String("Exit"));
	exitButton->connect("pressed", [&]() {window.close(); });
	gui.add(exitButton);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}

		window.clear();
		window.draw(backgrd);
		gui.draw();
		window.display();
	}
}
