#include "TextBox.h"
#include <sstream>

TextBox::TextBox(const sf::Font& font)
{
	text.setFont(font);
	text.setString("DEBUG_DEFAULT_STRING");
	text.setCharacterSize(16);
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(5, 5));	//the distance to the background is 5,5 ...temporary

	rect.setFillColor(sf::Color(192, 192, 192, 255));
	m_setOpacity(255);
	rect.setSize(sf::Vector2f(text.getGlobalBounds().width + 10, text.getCharacterSize() + 10));

	rowSize = 20;
}

//set the background texture of the textbox
void TextBox::setTexture(const sf::Texture* ptrTexture)
{
	//change to default color first
	rect.setFillColor(sf::Color(0, 0, 0, 255));
	rect.setTexture(ptrTexture);
}

//set the background color(if no texture is used)
void TextBox::setColor(const sf::Color& color)
{
	rect.setFillColor(color);
}

//set the string of the text
void TextBox::setText(const std::string& string)
{
	text.setString(string);

	//reshape the current shape
	m_reshape();
}

//set how many characters can be in the same row
void TextBox::setRowsize(int size)
{
    if(rowSize > 0)
    {
        rowSize = size;
        
        //reshape the current shape
        m_reshape();
    }
}

//set the size of the character
void TextBox::setCharacterSize(int size)
{
	text.setCharacterSize(size);
}

//move the textBox
void TextBox::move(const sf::Vector2f& displacement)
{
	rect.move(displacement);
	text.move(displacement);
}

//set the position of the textBox
void TextBox::setPosition(const sf::Vector2f& position)
{
	rect.setPosition(position);
	text.setPosition(position + sf::Vector2f(5, 5));
}

//set the texture background's rect
void TextBox::setTextureRect(const sf::IntRect& area)
{
	rect.setTextureRect(area);
}

//draw the textBox on the screen
void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(text, states);
}

//set the Opacity
void TextBox::m_setOpacity(const int& value)
{
	AnimationObject::setOpacity(value);
	sf::Color temp = rect.getFillColor();
	temp.a = value;
	rect.setFillColor(temp);

	temp = text.getColor();
	temp.a = value;
	text.setColor(temp);
}

//reshape the textBox
void TextBox::m_reshape()
{
    std::stringstream stream(text.getString());
    std::string result, temp;
    int count = 0;
    int num_Lines = 1;
    while(!stream.eof())
    {
        stream >> temp;
        //temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
        //temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
        
        //first check if the temp is bigger than rowSize
        if(temp.size() > rowSize)
        {
            //yes, than cut at the middle
            for(int i = 0; i < (temp.size() / rowSize); i++)
            {
                temp.insert(rowSize - count + i * rowSize, "\n");
                num_Lines++;
            }
            
            result = result + temp + " ";
            count = 1;
        }
        else
        {
            count += temp.size();
            //if the result is bigger than rowSize...
            if(count > rowSize)
            {
                result = result + "\n" + temp + " ";
                count = static_cast<int>(temp.size());
                num_Lines++;
            }
            else
            {
                result = result + temp + " ";
                count++;
            }
        }

    }
    text.setString(result);
}