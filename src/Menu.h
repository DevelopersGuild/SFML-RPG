#ifndef MENU_H
#define MENU_H

#include "Configuration.h"
#include "Lobby.h"
#include "Connection.h"

/*
Menu class
the Menu game state
*/
class Menu
{
private:
	/*
	a reference to configuration
	*/
	Configuration& config;

	/*
	background music
	*/
	sf::Music *bgMusic;

	/*
	the states of menu
	getUserName: prompt user to input his/her name
	mainMenu   : show "start", "settings", "exit" button
	settings   : allow player to adjust configurations
	modeChoice : allow player to choose to be client or host
	connect    : prompt the player to input server's ip
	connecting : try to connect to server
	multiplayer_lobby      : the lobby after connection success
	when started, the state is mainMenu.
	*/
	enum STATE{getUserName, mainMenu, setting, modeChoice, connect, connecting, multiplayer_lobby} state;

	//the background of the menu
	sf::RectangleShape backgrd;

	//the gui interface of the menu
	tgui::Gui gui;

	/*
	The gui stuff that only shown in getUserName
	NOTE: Since other widgets are already in panel,
	so only panel is needed to be added to gui!
	*/
	struct GetUserName {
		tgui::Panel::Ptr panel;
		tgui::Button::Ptr confirm;
		tgui::EditBox::Ptr textBox;
		tgui::Label::Ptr prompt;

		void initialize(Configuration& config);
	} state_getUserName;

	/*
	The gui stuff that only shown in the mainMenu
	*/
	struct MainMenu {
		tgui::Panel::Ptr panel;
		tgui::Button::Ptr exitButton;
		tgui::Button::Ptr startButton;
		tgui::Button::Ptr settingButton;
		void initialize(Configuration& config);
	} state_mainMenu;

	/*
	The gui stuff that only shown in the settings
	*/
	struct Settings {
		tgui::Panel::Ptr panel;
		tgui::Button::Ptr backButton;
		tgui::Slider::Ptr MusVol;
		tgui::Label::Ptr text_musVol;
		tgui::Slider::Ptr sonVol;
		tgui::Label::Ptr text_sonVol;
		void initialize(Configuration& config);
	} state_settings;

	/*
	The gui stuff that only shown in modeChoice
	*/
	struct ModeChoice {
		tgui::Panel::Ptr panel;
		tgui::Button::Ptr client;
		tgui::Button::Ptr server;
		tgui::Button::Ptr back;
		void initialize(Configuration& config);
	} state_modeChoice;

	/*
	The gui stuff that only shown in connect
	*/
	struct Connect
	{
		tgui::Panel::Ptr panel;
		tgui::Button::Ptr backButton;
		tgui::Button::Ptr connectButton;
		tgui::EditBox::Ptr IPBox;
		tgui::Label::Ptr text;
		void initialize(Configuration& config);

	} state_connect;

	/*
	The gui stuff that only shown in connecting
	*/
	struct Connecting
	{
		tgui::Panel::Ptr panel;
		tgui::Label::Ptr text;
		tgui::Button::Ptr backButton;
		void initialize(Configuration& config);
	} state_connecting;

	/*
	The gui stuff that only shown in server Lobby
	*/
	std::unique_ptr<Lobby> lobbyPtr;

	/*
	the functions of changing state
	*/
	void toGetUserName();
	void toMainMenu();
	void tomodeChoice();
	void toSetting();
	void toConnect();
	void toConnecting();
	void toLobby(sf::IpAddress& serverIp);	//if IP is valid, it is client. If Ip is invalid, it is server.

	//Try to connect to server
	bool tryConnect(sf::IpAddress& ip);

	//The drawing function
	void draw();
public:
	Menu() = delete;
	Menu(const Menu&) = delete;
	Menu operator=(const Menu&) = delete;

	Menu(Configuration&);

	//if game start, return true. If exit, return false
	std::unique_ptr<StartInfo> run();
};
#endif
