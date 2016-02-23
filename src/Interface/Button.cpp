#include "Button.h"

Button::Button() :texture(nullptr), texture_focus(nullptr)
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	setOpacity(0);
	//do nothing unless the user has set the function "onClick"
	onClickFunc = [](){};
    onRelease = [](){};
}

Button::Button(sf::Texture *texture, sf::Texture *texture_focus): Button()
{
	setButtonTexture(texture, texture_focus);
	setNormal();
}

Button::~Button()
{

}

void Button::setButtonTexture(sf::Texture *original, sf::Texture *focus)
{
	rect.setOutlineThickness(0);
	texture = original;
	texture_focus = focus;
}

bool Button::isOnButton(const sf::Vector2f& mouseposition) const
{
	return rect.getGlobalBounds().contains(mouseposition);
}

void Button::setNormal()
{
	if (texture)
	rect.setTexture(texture);
}

void Button::setFocus()
{
	if (texture_focus)
	rect.setTexture(texture_focus);
}

void Button::processEvent(const sf::RenderWindow& window, const sf::Event& event)
{
	sf::Vector2f mouseposition = sf::Vector2f(sf::Mouse::getPosition(window));

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isOnButton(mouseposition))
		{
			setFocus();
			onClickFunc();
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		setNormal();
	}

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
}