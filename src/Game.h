#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Configuration.h"

/*
The Game class
Handle the major game states and provides configuration
settings and inputs.
*/
class Game
{
private:
	//game window
	sf::RenderWindow window;

	/*
	Different game states
	preMenu: loading textures.
	Menu: Menu.
	setting: resolution, input key....
	preGame: multiplayer connection lobby, game settings
	inGame: inside the Game
	*/
	enum GAME_STATES{ preMenu, Menu, settings, preGame, inGame} states;

	//configuration
	Configuration config;
public:
	Game();

	//start the game
	void start();
};

#endif