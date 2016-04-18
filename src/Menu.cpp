#include "Menu.h"
Menu::Menu(Configuration & newConfig) :
	config(newConfig),
	gui(config.window)
{
	/*
	initialize the menu state
	*/
	state = STATE::getUserName;
	gui.setFont(tgui::Font(config.fontMan.get("Carlito-Bold.ttf")));	//set the default font of gui

	/*
	initialize the background
	*/
	backgrd.setSize(sf::Vector2f(config.window.getSize()));
	backgrd.setTexture(&config.texMan.get("Tower1.png"));

	/*
	initialize the getUserName gui
	*/
	state_getUserName.initialize(config);

	state_getUserName.confirm->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu();
	});

	/*
	initialize the mainMenu gui
	*/	
	state_mainMenu.initialize(config);

	state_mainMenu.startButton->connect("mousereleased", [&]()
	{
		config.soundMan.get("Decision2.ogg").play();
		tomodeChoice();
	});

	state_mainMenu.settingButton->connect("mousereleased", [&]()
	{
		config.soundMan.get("Decision2.ogg").play();
		toSetting();
	});

	state_mainMenu.exitButton->connect("mousereleased", [&]() {config.window.close(); });

	/*
	initialize the setting gui
	*/
	state_settings.initialize(config);

	state_settings.backButton->connect("mousereleased", [&]()
	{
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu();
	});

	state_settings.MusVol->connect("valuechanged",
		[&]() {
		float value = state_settings.MusVol->getValue() * 10.f;
		config.musMan.setVolume(value);
	});

	state_settings.sonVol->connect("valuechanged",
		[&]() {
		float value = state_settings.sonVol->getValue() * 10.f;
		config.soundMan.setVolume(value);
	});

	/*
	initialize modeChoice gui
	*/
	state_modeChoice.initialize(config);

	state_modeChoice.client->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toConnect();
	});

	state_modeChoice.server->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toLobby(Lobby::TYPE::server);
	});

	state_modeChoice.back->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		toMainMenu();
	});

	/*
	initialize connect gui
	*/
	state_connect.initialize(config);

	state_connect.backButton->connect("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		tomodeChoice();
	});
}

bool Menu::run()
{
	sf::RenderWindow& window(config.window);

	toGetUserName();

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

void Menu::toGetUserName()
{
	gui.removeAllWidgets();
	state = STATE::getUserName;
	gui.add(state_getUserName.panel);
}

void Menu::toMainMenu()
{
	gui.removeAllWidgets();
	state = STATE::mainMenu;
	gui.add(state_mainMenu.panel);
}

void Menu::tomodeChoice()
{
	gui.removeAllWidgets();
	state = STATE::modeChoice;
	gui.add(state_modeChoice.panel);
}

void Menu::toSetting()
{
	gui.removeAllWidgets();
	state = STATE::setting;
	gui.add(state_settings.panel);
}

void Menu::toConnect()
{
	gui.removeAllWidgets();
	state = STATE::connect;
	gui.add(state_connect.panel);
	state_connect.panel->hide();
	state_connect.panel->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.2));
}

void Menu::toLobby(Lobby::TYPE type)
{
	gui.removeAllWidgets();
	state = STATE::multiplayer_lobby;
	lobbyPtr.reset(new Lobby(config, type));
	lobbyPtr->addTgui(gui);
	lobbyPtr->hide();
	lobbyPtr->showWithEffect();

	lobbyPtr->connectBackButton("mousereleased", [&]() {
		config.soundMan.get("Decision2.ogg").play();
		lobbyPtr.release();
		tomodeChoice();
	});
}

void Menu::draw()
{
	config.window.draw(backgrd);
	gui.draw();
	config.window.draw(config.cursor);
}

void Menu::GetUserName::initialize(Configuration& config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(410, 192);
	panel->setPosition(307, 288);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 60));

	confirm = std::make_shared<tgui::Button>();
	panel->add(confirm);
	confirm->setText("Confirm");
	confirm->setPosition(135, 152);

	textBox = std::make_shared<tgui::EditBox>();
	panel->add(textBox);
	textBox->setText("Your Name");
	textBox->setPosition(85, 102);

	prompt = std::make_shared<tgui::Label>();
	panel->add(prompt);
	prompt->setText("Input your name:");
	prompt->setPosition(85, 72);
}

void Menu::MainMenu::initialize(Configuration & config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setPosition(800, 200);
	panel->setSize(200, 400);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 0));

	startButton = std::make_shared<tgui::Button>();
	panel->add(startButton);
	startButton->setText("Start");
	startButton->setPosition(10, 10);

	settingButton = std::make_shared<tgui::Button>();
	panel->add(settingButton);
	settingButton->setText("Setting");
	settingButton->setPosition(10, 110);

	exitButton = std::make_shared<tgui::Button>();
	panel->add(exitButton);
	exitButton->setText("Exit");
	exitButton->setPosition(10, 210);
}

void Menu::Settings::initialize(Configuration & config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(sf::Vector2f(700, 500));
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 60));
	panel->setPosition(200, 200);

	backButton = std::make_shared<tgui::Button>();
	panel->add(backButton);
	backButton->setText("Back");
	backButton->setPosition(65, 420);

	MusVol = std::make_shared<tgui::Slider>();
	panel->add(MusVol);
	MusVol->setPosition(150, 160);
	MusVol->setSize(200, 18);
	MusVol->setValue(10);

	text_musVol = std::make_shared<tgui::Label>();
	panel->add(text_musVol);
	text_musVol->setText("Music Volume");
	text_musVol->setPosition(150, 130);

	sonVol = std::make_shared<tgui::Slider>();
	panel->add(sonVol);
	sonVol->setPosition(150, 230);
	sonVol->setSize(200, 18);
	sonVol->setValue(10);

	text_sonVol = std::make_shared<tgui::Label>();
	panel->add(text_sonVol);
	text_sonVol->setText("Sound Volume");
	text_sonVol->setPosition(150, 200);
}

void Menu::ModeChoice::initialize(Configuration & config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setPosition(800, 200);
	panel->setSize(200, 400);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 0));

	client = std::make_shared<tgui::Button>();
	panel->add(client);
	client->setText("Join gmae");
	client->setPosition(10, 10);

	server = std::make_shared<tgui::Button>();
	panel->add(server);
	server->setText("Host game");
	server->setPosition(10, 110);

	back = std::make_shared<tgui::Button>();
	panel->add(back);
	back->setText("Back");
	back->setPosition(10, 210);
}

void Menu::Connect::initialize(Configuration & config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(410, 192);
	panel->setPosition(307, 288);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 60));

	backButton = std::make_shared<tgui::Button>();
	panel->add(backButton);
	backButton->setText("Back");
	backButton->setPosition(50, 130);

	connectButton = std::make_shared<tgui::Button>();
	panel->add(connectButton);
	connectButton->setText("Connect");
	connectButton->setPosition(230, 130);

	IPBox = std::make_shared<tgui::EditBox>();
	panel->add(IPBox);
	IPBox->setSize(300, 25);
	IPBox->setTextSize(18);
	IPBox->setPosition(50, 80);
	IPBox->setMaximumCharacters(15);
	IPBox->setInputValidator("[0-9]*\\.?[0-9]*\\.?[0-9]*\\.?[0-9]*");

	text_prompt = std::make_shared<tgui::Label>();
	panel->add(text_prompt);
	text_prompt->setText("Enter the IP:");
	text_prompt->setPosition(50, 50);
}
