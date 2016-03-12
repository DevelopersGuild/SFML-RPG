#pragma once
#include <SFML/Graphics.hpp>

/*
Cursor class
Handle cursor's event and sprite
*/
class Cursor : public sf::Drawable
{
private:
	sf::Sprite logo;

	sf::RenderWindow& window;
public:
	Cursor() = delete;
	Cursor(const Cursor&) = delete;

	Cursor(sf::RenderWindow& newWindow);

	sf::Vector2f getPosition();

	void setLogo(const sf::Texture& texture, const sf::IntRect& intrect);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update();
};