#include "Cursor.h"

Cursor::Cursor(sf::RenderWindow & newWindow) :
	window(newWindow)
{

}

sf::Vector2f Cursor::getPosition()
{
	return sf::Vector2f(sf::Mouse::getPosition(window));
}

void Cursor::setLogo(const sf::Texture& texture, const sf::IntRect& intrect) 
{
	logo.setTexture(texture);
	logo.setTextureRect(intrect);
}

void Cursor::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(logo);
}

void Cursor::update()
{
	logo.setPosition(getPosition());
}
