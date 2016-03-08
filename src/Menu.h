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
	Configuration& config;
public:
	Menu() = delete;
	Menu(const Menu&) = delete;
	Menu operator=(const Menu&) = delete;

	Menu(Configuration&);

	void run();
};
#endif
