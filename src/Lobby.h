#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

/*
Lobby class
The multiplayer lobby is a special state in the Menu that handles everything before
the game start.

Client: Show the name of other players, and allow players to chat in dialog box
Server: In addition of client, the server can set the map and enable advanced options, and start the game.
*/
class Lobby final
{
private:

public:
	/*
	run function
	Add all tgui widget to gui render
	
	gui			: the gui render
	connection	: the lobby needs to access internect interface, whether it is server or client.
	config		: the configuration for accessing resources
	*/
	void run();

	/*
	gameStart function
	Finalize the game setting and start the game.
	*/
	void gameStart();

	/*
	update function
	check the connection and update the signal from server/ client
	*/
	void update();
};