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
	preMenu.release();

	bool result;
	do
	{
		std::unique_ptr<Menu> menu(new Menu(config));
		result = menu->run();
		menu.release();
		if (result)
		{
			//std::unique_ptr<inGame> inGame<new inGame(config));
			//result = inGame->run();
			//inGame.release();
		}
	} while (result);
}
