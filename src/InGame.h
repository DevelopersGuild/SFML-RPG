#pragma once
#include "Configuration.h"
#include "StartInfo.h"
#include <TGUI/TGUI.hpp>

/*
InGame class
handles the main game process.
*/
class InGame
{
private:
	Configuration& config;
    enum STATE{loading, inMap, battle, cinematic} state;
public:
	InGame() = delete;
	InGame(const InGame&) = delete;
	InGame operator=(const InGame&) = delete;
	InGame(const InGame&&) = delete;

	InGame(Configuration& config, std::unique_ptr<StartInfo> info);
	void run();
};