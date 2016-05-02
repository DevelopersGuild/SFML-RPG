#include "GameInterface.h"
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) : 
	system(newSystem)
{

}

void Gameplay::GameInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameData& gameData = system->gameData;
	target.draw(gameData.getMap());
	
	//testing only, TBD
	std::list<Player>& playerList = gameData.getPlayerList();
	for (Player& player : playerList)
	{
		target.draw(player);
	}
}
