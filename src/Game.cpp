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

	std::unique_ptr<Menu> menu(new Menu(config));
	menu->run();
	menu.release();
}
