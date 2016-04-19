#pragma once

#include <TGUI/TGUI.hpp>
#include "Configuration.h"
#include "Connection.h"

/*
Lobby class
Handles the system and the API of multiplayer lobby before the game starts.
Note: Since other widgets are already in panel, so only panel is needed to be added to gui!
*/

class Lobby
{
public:
	//the type of Lobby: client or server?
	enum TYPE { client, server };
private:
	Configuration& config;		//reference to configuration

	tgui::Panel::Ptr panel;
	tgui::Button::Ptr backButton;
	tgui::Button::Ptr startButton;
	tgui::ChatBox::Ptr chatBox;
	tgui::TextBox::Ptr chatInput;
	tgui::Button::Ptr chatInputButton;
	tgui::Picture::Ptr mapPicture;
    
    //the lobby needs connection
    Connection connection;

	//type of lobby
	TYPE type;

	//function to initialize the gui
	void initialize();

	//handles the incoming packet
	void handlePacket(sf::Packet& packet);

public:
	Lobby() = delete;
	Lobby(const Lobby&) = delete;
	Lobby operator=(const Lobby&) = delete;

	//constructor for client
	Lobby(Configuration& config, sf::IpAddress serverIp);
	//constructor for server
	Lobby(Configuration& config);

	//add the panel to gui
	void addTgui(tgui::Gui& gui);

	//connect the backButton
	template<typename Func, typename...Args>
	unsigned int connectBackButton(const std::string& signalNames, Func func, Args... args)
	{
		return backButton->connect(signalNames, func, args...);
	}

	//connect the startButton
	template<typename Func, typename...Args>
	unsigned int connectStartButton(const std::string& signalNames, Func func, Args... args)
	{
		return startButton->connect(signalNames, func, args...);
	}

	//hide the panel
	void hide();

	//show the panel
	void show();

	//show the panel with effect
	void showWithEffect();

	//update the lobby's data
	void update();
};