#include "GameInterface.h"
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) :
	system(newSystem)
{
	camera.setSize(500, 375);

	//initialize the transitionRect
	gui.setWindow(system->config.window);
	transitionRect = std::make_shared<tgui::Panel>();
	gui.add(transitionRect);
	transitionRect->setBackgroundColor(tgui::Color(sf::Color::Black));
	transitionRect->hide();
}

void Gameplay::GameInterface::draw()
{
	sf::RenderWindow& window = system->config.window;
	updateCamera();	//update the camera
	window.draw(*system->currentMap);
	window.draw(*system->thisPlayerPtr);
	gui.draw();
	//debug
	
	system->currentMap->Draw(system->config.window, tmx::MapLayer::DrawType::Debug, true);
}

//Peter's function
void Gameplay::GameInterface::updateCamera()
{
	//get the map size, player's position, and camera size
	const sf::Vector2u& currentMapSize = system->currentMap->GetMapSize();
	const sf::Vector2f& playerPosition = system->thisPlayerPtr->getPosition();
	const sf::Vector2f& cameraSize = camera.getSize();

	//******************************************************************************
	//Peter's part
	//example: the camera stops at some point when player approach the top of the map
	if (playerPosition.y < cameraSize.y / 2) 
	{
		camera.setCenter(playerPosition.x, cameraSize.y / 2);
	}
	else
	{
		camera.setCenter(playerPosition);
	}

	//....
	//....
	//....

	//end of Peter's part
	//******************************************************************************
	//ask window to draw the camera in the next render function
	system->config.window.setView(camera);
}

void Gameplay::GameInterface::setTransition()
{
	//set the transitionRect to the right of the current camera
	transitionRect->setSize(gui.getSize());
	//const sf::Vector2f& viewSize = view.getSize();

	transitionRect->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::seconds(0.2));

	//render loop to make sure Transition animation is not called again in 0.2s
	sf::Clock clock;
	sf::RenderWindow& window = system->config.window;
	while (clock.getElapsedTime() < sf::seconds(0.2))
	{
		window.clear();
		this->draw();
		window.display();
	}
}

void Gameplay::GameInterface::exitTransition()
{
	transitionRect->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::seconds(0.2));

	//render loop to make sure Transition animation is not called again in 0.2s
	sf::Clock clock;
	sf::RenderWindow& window = system->config.window;
	while (clock.getElapsedTime() < sf::seconds(0.2))
	{
		window.clear();
		this->draw();
		window.display();
	}
}
