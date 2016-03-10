#include "Menu.h"
Menu::Menu(Configuration & newConfig) :
	config(newConfig),
	gui(config.window)
{
	/*
	initialize the menu state
	*/
	state = STATE::mainMenu;

	/*
	initialize the background
	*/
	backgrd.setSize(sf::Vector2f(config.window.getSize()));
	backgrd.setTexture(&config.texMan.get("Texture/Tower1.png"));

	/*
	initialize the mainMenu gui
	*/	
	startButton = std::make_shared<tgui::Button>();
	startButton->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	startButton->setText("Start");
	//startButton->connect(
	startButton->setPosition(800, 200);

	settingButton = std::make_shared<tgui::Button>();
	settingButton->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	settingButton->setText("Setting");
	settingButton->connect("mousereleased", [&]() {toSetting(); });
	settingButton->setPosition(800, 300);

	exitButton = std::make_shared<tgui::Button>();
	exitButton->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	exitButton->setText("Exit");
	exitButton->connect("mousereleased", [&]() {config.window.close(); });
	exitButton->setPosition(800, 400);

	/*
	initialize the setting gui
	*/
	setRect.setSize(sf::Vector2f(700, 500));
	setRect.setFillColor(sf::Color(255, 255, 255, 180));
	setRect.setPosition(sf::Vector2f(200, 200));

	setting_backButton = std::make_shared<tgui::Button>();
	setting_backButton->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	setting_backButton->setText("Back");
	setting_backButton->connect("mousereleased", [&]() {toMainMenu(); });
	setting_backButton->setPosition(200, 700);

	setting_MusVol = std::make_shared<tgui::Slider>();
	setting_MusVol->setPosition(500, 500);
	setting_MusVol->setSize(200, 18);
	setting_MusVol->setValue(10);

	setting_text_musVol = std::make_shared<tgui::Label>();
	setting_text_musVol->setFont(tgui::Font(config.fontMan.get("Texture/arial.ttf")));
	setting_text_musVol->setText("Music Volume");
	setting_text_musVol->setPosition(500, 470);
}

bool Menu::run()
{
	sf::RenderWindow& window(config.window);

	toMainMenu();

	sf::Music& bgMusic = config.musMan.get("Music/Theme1.ogg");
	bgMusic.play();

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
		draw();
		window.display();
	}
	return false;
}

void Menu::toMainMenu()
{
	gui.removeAllWidgets();
	state = STATE::mainMenu;
	gui.add(startButton);
	gui.add(settingButton);
	gui.add(exitButton);
}

void Menu::toSetting()
{
	gui.removeAllWidgets();
	state = STATE::setting;
	gui.add(setting_backButton);
	gui.add(setting_MusVol);
	gui.add(setting_text_musVol);
}

void Menu::draw()
{
	config.window.draw(backgrd);

	switch (state)
	{
	case Menu::mainMenu:
		break;
	case Menu::setting:
		config.window.draw(setRect);
		break;
	case Menu::connect:
		break;
	case Menu::lobby:
		break;
	default:
		break;
	}

	gui.draw();
}
