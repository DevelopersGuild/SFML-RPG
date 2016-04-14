#ifndef MENU_H
#define MENU_H

#include "Configuration.h"

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
	mainMenu   : show "start", "settings", "exit" button
	settings   : allow player to adjust configurations
	modeChoice : allow player to choose to be client or host
	connect    : prompt the player to input server's ip
	lobby      : the lobby after connection success
	when started, the state is mainMenu.
	*/
	enum STATE{mainMenu, setting, modeChoice, connect, lobby} state;

	/*
	the functions of changing state
	*/
	void toMainMenu();
	void tomodeChoice();
	void toSetting();
	void toConnect();

	//the background of the menu
	sf::RectangleShape backgrd;

	//the gui interface of the menu
	tgui::Gui gui;

	/*
	The gui stuff that only shown in the mainMenu
	*/
	tgui::Button::Ptr exitButton;
	tgui::Button::Ptr startButton;
	tgui::Button::Ptr settingButton;

	/*
	The gui stuff that only shown in the settings
	*/
	sf::RectangleShape setRect;
	tgui::Button::Ptr setting_backButton;
	tgui::Slider::Ptr setting_MusVol;
	tgui::Label::Ptr setting_text_musVol;
	tgui::Slider::Ptr setting_sonVol;
	tgui::Label::Ptr setting_text_sonVol;

	/*
	The gui stuff that only shown in modeChoice
	*/
	tgui::Button::Ptr modeChoice_client;
	tgui::Button::Ptr modeChoice_server;
	tgui::Button::Ptr modeChoice_back;

	/*
	The gui stuff that only shown in connection
	*/
	sf::RectangleShape conRect;
	tgui::Button::Ptr connect_backButton;
	tgui::Button::Ptr connect_connectButton;
	tgui::EditBox::Ptr connect_IPBox;
	tgui::Label::Ptr connect_text_prompt;

	/*
	The gui stuff that only shown in server Lobby
	*/

	/*
	The drawing function
	*/
	void draw();

public:
	Menu() = delete;
	Menu(const Menu&) = delete;
	Menu operator=(const Menu&) = delete;

	Menu(Configuration&);

	//if game start, return true. If exit, return false
	bool run();
};
#endif
