#ifndef TINS_INTERFACE_BUTTON
#define TINS_INTERFACE_BUTTON

#include <SFML/Graphics.hpp>
#include "InterfaceEvent.h"
#include "AnimationObject.h"
#include <functional>

/*
Button class
*/
class Button :
	public InterfaceEvent,
	public AnimationObject,
	public sf::Drawable
{
private:
    //the rectangle that holds the button
    sf::RectangleShape rect;

	//the pointers to texture
	sf::Texture *texture;
	sf::Texture *texture_focus;

	//functions
	//change texture to normal
	void setNormal();
	//change texture to focus
	void setFocus();
	//the function when clicked
	std::function<void()> onClickFunc;
    //the function when release
    std::function<void()> onRelease;

	//implement AnimationObject
	sf::Vector2f animation_getPosition(){ return rect.getPosition(); }
	void animation_Move(sf::Vector2f displacement){ rect.move(displacement); }
	void animation_setPosition(sf::Vector2f position){ rect.setPosition(position); }
	void setOpacity(int value)
	{ 
		AnimationObject::setOpacity(value);
		sf::Color temp = rect.getFillColor();
		rect.setFillColor(sf::Color(temp.r, temp.g, temp.b, value));
	}

public:
	Button();
	Button(sf::Texture *texture, sf::Texture *texture_focus);
	virtual ~Button();

	//set the texture of button(original texture, and focus texture)
	void setButtonTexture(sf::Texture *texture, sf::Texture *texture_focus);

	//is cursor on the button?
	bool isOnButton(const sf::Vector2f&) const;

	//processEvent
	virtual void processEvent(const sf::RenderWindow& window, const sf::Event& event);

	//set user-defined function when button is clicked
	void setOnClick(std::function<void()> function) { onClickFunc = function; }
    
    //set user-defined function when button is released
    void setOnRelease(std::function<void()> function){ onRelease = function;}

	//draw the button on the target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//set the size of the button
	void setSize(const sf::Vector2f& size){ rect.setSize(size); }

	//get the size of the button
	sf::Vector2f getSize(){ return rect.getSize(); }

	//set the position of the button
	void setPosition(const sf::Vector2f& position){ rect.setPosition(position); }

	//get the position of the button
	sf::Vector2f getPosition(){ return rect.getPosition(); }
    
};
#endif