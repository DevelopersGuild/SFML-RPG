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
		tomodeChoice();
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
	initialize modeChoice gui
	*/
	modeChoice_client = std::make_shared<tgui::Button>();
	modeChoice_client->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	modeChoice_client->setText("Join gmae");
	modeChoice_client->setPosition(800, 200);
	modeChoice_client->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toConnect();
	});

	modeChoice_server = std::make_shared<tgui::Button>();
	modeChoice_server->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	modeChoice_server->setText("Host game");
	modeChoice_server->setPosition(800, 300);
	modeChoice_server->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toLobby();
	});

	modeChoice_back = std::make_shared<tgui::Button>();
	modeChoice_back->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	modeChoice_back->setText("Back");
	modeChoice_back->setPosition(800, 400);
	modeChoice_back->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu();
	});

	/*
	initialize connect gui
	*/
	sf::Vector2f size = sf::Vector2f(410, 192);
	conRect.setSize(size);
	conRect.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f windowSize = sf::Vector2f(config.window.getSize());
	conRect.setPosition(windowSize.x / 2, windowSize.y / 2);
	conRect.setFillColor(sf::Color(0, 0, 0, 60));

	connect_backButton = std::make_shared<tgui::Button>();
	connect_backButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_backButton->setText("Back");
	connect_backButton->setPosition(360, 400);
	connect_backButton->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		tomodeChoice();
	});

	connect_connectButton = std::make_shared<tgui::Button>();
	connect_connectButton->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_connectButton->setText("Connect");
	connect_connectButton->setPosition(540, 400);

	connect_IPBox = std::make_shared<tgui::EditBox>();
	connect_IPBox->setSize(300, 25);
	connect_IPBox->setTextSize(18);
	connect_IPBox->setPosition(360, 350);
	connect_IPBox->setMaximumCharacters(15);
	connect_IPBox->setInputValidator("[0-9]*\\.?[0-9]*\\.?[0-9]*\\.?[0-9]*");

	connect_text_prompt = std::make_shared<tgui::Label>();
	connect_text_prompt->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	connect_text_prompt->setText("Enter the IP:");
	connect_text_prompt->setPosition(360, 320);

	/*
	initialize multiplayer lobby gui
	*/
	lobby_panel = std::make_shared<tgui::Panel>();
	lobby_panel->setSize(822, 614);
	lobby_panel->setPosition(102, 77);
	lobby_panel->setBackgroundColor(tgui::Color(0, 0, 0, 60));
	lobby_panel->setFont(tgui::Font(config.fontMan.get("arial.ttf")));

	lobby_back = std::make_shared<tgui::Button>();
	lobby_panel->add(lobby_back);
	lobby_back->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	lobby_back->setText("Back");
	lobby_back->setPosition(65, 542);
	lobby_back->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		//reset lobby...
		tomodeChoice();
	});

	lobby_start = std::make_shared<tgui::Button>();
	lobby_panel->add(lobby_start);
	lobby_start->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	lobby_start->setText("Start");
	lobby_start->setPosition(571, 546);
	lobby_start->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		//start game...
	});

	lobby_chatBox = std::make_shared<tgui::ChatBox>();
	lobby_panel->add(lobby_chatBox);
	lobby_chatBox->setSize(340, 150);
	lobby_chatBox->setPosition(51, 323);
	lobby_chatBox->addLine("Test");

	lobby_textBox = std::make_shared<tgui::TextBox>();
	lobby_panel->add(lobby_textBox);
	lobby_textBox->setSize(340, 22);
	lobby_textBox->setPosition(51, 473);
	lobby_textBox->setMaximumCharacters(33);

	lobby_send = std::make_shared<tgui::Button>();
	lobby_panel->add(lobby_send);
	lobby_send->setSize(34, 22);
	lobby_send->setFont(tgui::Font(config.fontMan.get("arial.ttf")));
	lobby_send->setPosition(357, 473);
	lobby_send->setText("send");
	lobby_send->connect("mousereleased", [&]() {
		lobby_chatBox->addLine(lobby_textBox->getText());
		lobby_textBox->setText("");
	});

	lobby_mapPicture = std::make_shared<tgui::Picture>();
	lobby_panel->add(lobby_mapPicture);
	lobby_mapPicture->setSize(234, 210);
	lobby_mapPicture->setPosition(535, 50);
	lobby_mapPicture->setTexture(config.texMan.get("Tower1.png"));
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

void Menu::tomodeChoice()
{
	gui.removeAllWidgets();
	state = STATE::modeChoice;
	gui.add(modeChoice_client);
	gui.add(modeChoice_server);
	gui.add(modeChoice_back);
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

void Menu::toLobby()
{
	gui.removeAllWidgets();
	state = STATE::multiplayer_lobby;
	gui.add(lobby_panel);
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
	case Menu::multiplayer_lobby:
		break;
	default:
		break;
	}

	gui.draw();
	config.window.draw(config.cursor);
}

