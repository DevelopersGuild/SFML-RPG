#include "Game.h"

Game::Game()
{
	//when the game starts, the state is preMenu.
	states = GAME_STATES::preMenu;
}

void Game::start() 
{
	std::unique_ptr<PreMenu> preMenu(new PreMenu(config));
	preMenu->run();
	preMenu.reset();

	//do
	//{
	std::unique_ptr<Menu> menu(new Menu(config));
	std::unique_ptr<StartInfo> startInfo = menu->run();
	menu.reset();

	if (startInfo) //if startInfo is valid, start the game
	{
		//std::unique_ptr<inGame> inGame<new inGame(config));
		//result = inGame->run();
		//inGame.reset();
	}
	//} while (result);
}
