#include "GameInterface.h"
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) : 
	system(newSystem)
{
	sf::RenderWindow& window = system->config.window;
	camera.setSize(500, 375);

	//initialize the transitionRect
	//transitionRect.setFillColor(sf::Color::Black);
	gui.setWindow(system->config.window);
	transitionRect = std::make_shared<tgui::Panel>();
	gui.add(transitionRect);
	transitionRect->setBackgroundColor(tgui::Color(sf::Color::Black));
	transitionRect->hide();
}

void Gameplay::GameInterface::draw()
{
	sf::RenderWindow& window = system->config.window;
	camera.setCenter(system->player->getPosition());
	system->config.window.setView(camera);
	window.draw(system->map);
	window.draw(*system->player);
	gui.draw();
	//debug
	//system->map.Draw(system->config.window, tmx::MapLayer::DrawType::Debug, true);
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
