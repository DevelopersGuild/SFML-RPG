#ifndef GAME_H
#define GAME_H

#include "Configuration.h"
#include "PreMenu.h"
#include "Menu.h"
#include "InGame.h"

/*
The Game class
Handle the major game states and provides configuration
settings and inputs.
*/
class Game
{
private:
	/*
	Different game states
	preMenu: loading textures.
	Menu: Menu.
	inGame: inside the Game
	*/
	enum GAME_STATES{ preMenu, inMenu, inGame} states;

	//configuration
	Configuration config;
    
public:
	Game();

	//start the game
	void start();
};

#endif