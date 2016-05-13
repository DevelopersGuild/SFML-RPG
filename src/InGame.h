#pragma once
#include "Configuration.h"
#include "StartInfo.h"
#include <TGUI/TGUI.hpp>
#include "GameInterface.h"
#include "GameNetwork.h"
#include "ServerSystem.h"
#include "ClientSystem.h"

/*
InGame class
handles the main game process.
*/
class InGame
{
private:
	Configuration& config;
	sf::Clock clock;	//untility clock

	//the network model of the game. It handles the input from internet
	Gameplay::GameNetwork* networkPtr;

	//the game system
	Gameplay::GameSystem* systemPtr;

	//the interface of the game handles graphics.
	Gameplay::GameInterface* interfacePtr;

	//First phase: load the game
	void loadGame(std::unique_ptr<StartInfo>& startInfo);

	//Second phase: send/receive startGame signal
	//client: send "ready" signal to server for every 5s; server: start anyway
	bool waitForStart(std::unique_ptr<StartInfo>&,Connection*);
public:
	InGame() = delete;
	InGame(const InGame&) = delete;
	InGame operator=(const InGame&) = delete;
	InGame(const InGame&&) = delete;
	~InGame();

	InGame(Configuration& config, std::unique_ptr<StartInfo> info);
	void run();
};