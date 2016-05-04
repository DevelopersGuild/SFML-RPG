#include "GameInterface.h"
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) : 
	system(newSystem)
{

}

void Gameplay::GameInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(system->map);
	target.draw(*system->player);

	//debug
	//system->map.Draw(system->config.window, tmx::MapLayer::DrawType::Debug, true);
}
