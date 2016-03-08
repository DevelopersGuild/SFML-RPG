#ifndef PREMENU_H
#define PREMENU_H

#include <TGUI/TGUI.hpp>
#include "Configuration.h"
#include <thread>

/*
PreMenu class
a game state that initialize the resources and settings
*/
class PreMenu
{
private:
	Configuration& config;
public:
	PreMenu() = delete;
	PreMenu(const PreMenu&) = delete;
	PreMenu operator=(const PreMenu&) = delete;

	//constructor
	PreMenu(Configuration& config);

	//initialize the resources, return true is success
	//false otherwise
	bool initialize();
	
	/*
	run the preMenu:
	the first thread process event (so the user can close the 
	window at any time).
	the second thread read the resource and change the label.
	*/
	void run();
};
#endif
