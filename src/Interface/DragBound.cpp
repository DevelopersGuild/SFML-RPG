#include "DragBound.h"

DragBound::DragBound()
{
	selected = false;
}

DragBound::DragBound(const sf::Vector2f& size)
{
	selected = false;
	this->setSize(size);
}

DragBound::~DragBound()
{

}

void DragBound::processEvent(const sf::RenderWindow& window, const sf::Event& event)
{
	sf::Vector2f mouseposition = sf::Vector2f(sf::Mouse::getPosition(window));
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (contains(mouseposition))
		{
			mouse_previous = sf::Vector2f(sf::Mouse::getPosition(window));
			selected = true;
			stopAnimation();
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected)
		{
			sf::Vector2f change = mouseposition - mouse_previous;
			mouse_previous = mouseposition;
			move(change);
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		selected = false;
	}
}