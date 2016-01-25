#ifndef TINS_INTERFACE_TEXTBOX
#define TINS_INTERFACE_TEXTBOX

#include "AnimationObject.h"

/*
Textbox may be used as dialogBox, hints, messages or character's name...
The position of textbox is at its center, not the leftTop corner.
Textbox is not a button, nothing will happen when clicked.
Default : a gray box with text "DEFAULT_STRING", rowSize is 14
*/
class TextBox : public AnimationObject, public sf::Drawable
{
private:
	sf::RectangleShape rect;	//the background of the text
	sf::Text text;				//the text
	int rowSize;

	//AnimationObject implementation
	//define how to get the object's position for animation
	sf::Vector2f animation_getPosition(){ return rect.getPosition(); }
	//define how the object moves
	void animation_Move(sf::Vector2f displacement){ move(displacement); }
	//define how to set the object's position
	void animation_setPosition(sf::Vector2f position){ setPosition(position); }
	//define how the object set its opacity
	void setOpacity(int value){ m_setOpacity(value); }

	//set the Opacity
	void m_setOpacity(const int& value);

	//reshape the textBox
	void m_reshape();
public:
	TextBox(const sf::Font& font);
	
	//set the background texture of the textbox
	void setTexture(const sf::Texture* ptrTexture);

	//set the background color(if no texture is used)
	void setColor(const sf::Color& color);

	//set the string of the text
	void setText(const std::string& string);

	//set how many characters can be in the same row
	void setRowsize(int size);

	//set the size of the character
	void setCharacterSize(int size);

	//move the textBox
	void move(const sf::Vector2f& displacement);

	//set the position of the textBox
	void setPosition(const sf::Vector2f& position);

	//set the texture background's rect
	void setTextureRect(const sf::IntRect& rect);

	//draw the textBox on the screen
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif