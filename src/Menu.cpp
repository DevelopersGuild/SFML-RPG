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
	backgrd.setTexture(&config.texMan.get("Tower1.png"));

	/*
	initialize the mainMenu gui
	*/	
	startButton = std::make_shared<tgui::Button>();
	startButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	startButton->setText("Start");
	startButton->connect("mousereleased", [&]()
	{
		config.soundMan.get("Decision2.ogg").play();
		toConnect();
	});
	startButton->setPosition(800, 200);

	settingButton = std::make_shared<tgui::Button>();
	settingButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	settingButton->setText("Setting");
	settingButton->connect("mousereleased", [&]() 
	{
		config.soundMan.get("Decision2.ogg").play();
		toSetting(); 
	});
	settingButton->setPosition(800, 300);

	exitButton = std::make_shared<tgui::Button>();
	exitButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
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
	setting_backButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	setting_backButton->setText("Back");
	setting_backButton->connect("mousereleased", [&]() 
	{
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu(); 
	});
	setting_backButton->setPosition(200, 700);

	setting_MusVol = std::make_shared<tgui::Slider>();
	setting_MusVol->setPosition(500, 500);
	setting_MusVol->setSize(200, 18);
	setting_MusVol->setValue(10);
	setting_MusVol->connect("valuechanged",
		[&]() {
		float value = setting_MusVol->getValue() * 10.f;
		config.musMan.setVolume(value);
	});

	setting_text_musVol = std::make_shared<tgui::Label>();
	setting_text_musVol->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	setting_text_musVol->setText("Music Volume");
	setting_text_musVol->setPosition(500, 470);

	setting_sonVol = std::make_shared<tgui::Slider>();
	setting_sonVol->setPosition(500, 600);
	setting_sonVol->setSize(200, 18);
	setting_sonVol->setValue(10);
	setting_sonVol->connect("valuechanged", 
		[&]() {
		float value = setting_sonVol->getValue() * 10.f;
		config.soundMan.setVolume(value);
	});

	setting_text_sonVol = std::make_shared<tgui::Label>();
	setting_text_sonVol->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	setting_text_sonVol->setText("Sound Volume");
	setting_text_sonVol->setPosition(500, 570);

	/*
	initialize connect gui
	*/
	conRect.setSize(sf::Vector2f(700, 500));
	conRect.setPosition(sf::Vector2f(200, 200));
	conRect.setFillColor(sf::Color(255, 255, 255, 180));

	connect_backButton = std::make_shared<tgui::Button>();
	connect_backButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_backButton->setText("Back");
	connect_backButton->setPosition(400, 500);
	connect_backButton->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu();
	});

	connect_connectButton = std::make_shared<tgui::Button>();
	connect_connectButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_connectButton->setText("Connect");
	connect_connectButton->setPosition(600, 500);

	connect_IPBox = std::make_shared<tgui::EditBox>();
	connect_IPBox->setSize(300, 25);
	connect_IPBox->setTextSize(18);
	connect_IPBox->setPosition(400, 450);
	connect_IPBox->setMaximumCharacters(15);
	connect_IPBox->setInputValidator("[0-9]*\\.?[0-9]*\\.?[0-9]*\\.?[0-9]*");

	connect_text_prompt = std::make_shared<tgui::Label>();
	connect_text_prompt->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_text_prompt->setText("Enter the IP:");
	connect_text_prompt->setPosition(400, 420);
}

bool Menu::run()
{
	sf::RenderWindow& window(config.window);

	toMainMenu();

	bgMusic = &config.musMan.get("Theme1.ogg");
	bgMusic->setLoop(true);
	bgMusic->play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
			config.cursor.update();
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
	gui.add(setting_sonVol);
	gui.add(setting_text_sonVol);
}

void Menu::toConnect()
{
	gui.removeAllWidgets();
	state = STATE::connect;
	gui.add(connect_backButton);
	gui.add(connect_connectButton);
	gui.add(connect_IPBox);
	gui.add(connect_text_prompt);
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
		config.window.draw(conRect);
		break;
	case Menu::lobby:
		break;
	default:
		break;
	}

	gui.draw();
	config.window.draw(config.cursor);
}

