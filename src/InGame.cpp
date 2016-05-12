#include "InGame.h"
#include <sstream>

InGame::InGame(Configuration& newConfig, std::unique_ptr<StartInfo> startInfo) :
	config(newConfig)
{
	loadGame(startInfo);
}

InGame::~InGame()
{
	delete interfacePtr;
	delete networkPtr;
	delete systemPtr;
}

void InGame::run()
{
	sf::RenderWindow& window = config.window;
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		//input & update phase
		systemPtr->updateQuadTree();
		networkPtr->update();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    systemPtr->interact();
            }
            
			interfacePtr->updateGUI(event);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			systemPtr->movePlayer(config.player_name, Gameplay::Character::Direction::left);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			systemPtr->movePlayer(config.player_name, Gameplay::Character::Direction::right);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			systemPtr->movePlayer(config.player_name, Gameplay::Character::Direction::down);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			systemPtr->movePlayer(config.player_name, Gameplay::Character::Direction::up);

		config.cursor.update();

		//rendering phase
		window.clear();
		interfacePtr->draw();
		//window.draw(config.cursor);
		window.display();
	}
}

void InGame::loadGame(std::unique_ptr<StartInfo>& startInfo)
{
	//graphics in loading screen
	sf::RenderWindow& window = config.window;
	tgui::Gui gui;
	gui.setWindow(window);

	gui.setFont(tgui::Font(config.fontMan.get("Carlito-Bold.ttf")));

	tgui::Picture::Ptr background = std::make_shared<tgui::Picture>();
	background->setTexture(config.texMan.get("Book.png"));
	background->setSize(gui.getSize());
	gui.add(background);

	tgui::ProgressBar::Ptr progressBar = std::make_shared<tgui::ProgressBar>();
	gui.add(progressBar);
	progressBar->setPosition(50, 700);
	progressBar->setSize(930, 20);
	progressBar->setMinimum(0);
	progressBar->setMaximum(100);
	progressBar->setText("loading...0%");
	unsigned int percent = 0;
	sf::Clock clock;

	tgui::Panel::Ptr panel = std::make_shared<tgui::Panel>();
	gui.add(panel);
	panel->setSize(820, 200);
	panel->setPosition(100, 450);
	panel->setBackgroundColor(tgui::Color(192, 192, 192, 150));

	tgui::Label::Ptr tips = std::make_shared<tgui::Label>();
	panel->add(tips);
	tips->setPosition(20, 20);
	tips->setTextSize(24);
	tips->setText("This is testing. Click cross button to leave.");
	
	//the render loop
	while (window.isOpen() && percent < 99)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}

		config.cursor.update();

		if (clock.getElapsedTime() > sf::seconds(0.05))
		{
			percent++;
			std::stringstream ss;
			ss << percent;
			progressBar->setText(sf::String("loading...") + sf::String(ss.str()) + sf::String("%"));
			progressBar->setValue(percent);
			clock.restart();
		}
		window.clear();
		gui.draw();
		window.draw(config.cursor);
		window.display();
	}
	
	//if it is server, start server system...TBD
	systemPtr = new Gameplay::GameSystem(config, startInfo);
	if (startInfo->type == StartInfo::TYPE::Server)
	{
		//systemPtr = new Gameplay::ServerSystem(config);
	}
	else //else it is client, start client system
	{
		//systemPtr = new Gameplay::ClientSystem();
	}

	//create network and interface which is pointing to the game system
	networkPtr = new Gameplay::GameNetwork(systemPtr);
		
	systemPtr->setNetworkPtr(networkPtr);

	interfacePtr = new Gameplay::GameInterface(systemPtr);

	systemPtr->setInterfacePtr(interfacePtr);

	if (startInfo->type == StartInfo::TYPE::Server)
	{
		//send ready signal to every player
		//...
	}
	else //if it is a client
	{
		//wait for server's signal
	}
}

