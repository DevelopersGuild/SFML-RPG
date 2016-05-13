#pragma once
#include <SFML/Network.hpp>
#include <list>

/*
StartInfo struct
this class contains all necessary informations for the main game to start up.
The menu class fill in and return this class, then passed into Ingame class for initialization.
if the menu leaves, the type will be "exit".
*/
struct StartInfo
{
	//define StartInfo::Player
	struct Player {
		std::string name;
		sf::IpAddress ip;
		bool ready = false;
		enum Character{ SilverGuy, GoldGuy, RedGirl, BrownGirl } character;
	};

	//a list of StartInfo::Player
	std::list<StartInfo::Player> playerList;

	//define StartInfo::Map
	struct Map
	{
		std::string name;
		//TBD
	} map;

	sf::IpAddress serverIP;

	//type of the game
	enum TYPE {Client, Server} type;

	//game mode
	enum GAMEMODE{Coop, TwoTeam, Competitive} mode;
};