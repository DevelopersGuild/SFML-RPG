#include "Cursor.h"

Cursor::Cursor()
{
    
    
}

Cursor::Cursor(const sf::RenderWindow& newWindow)
{
    _window = &newWindow;
}

void Cursor::setState(Cursor::State state)
{
    _state = state;
}

sf::Vector2f Cursor::getPosition()
{
    if(_window != nullptr)
    {
        return sf::Vector2f(sf::Mouse::getPosition(*_window));
    }
    else
    {
        return sf::Vector2f(0,0);
    }
    
}

void Cursor::processEvent(const sf::RenderWindow& window, const sf::Event& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        _cursor_logo.setPosition(getPosition());
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        _state = State::clicking;
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        _state = State::normal;
    }
}

void Cursor::loadTexture(const sf::Texture& texture)
{
    _cursor_logo.setTexture(texture);
    //temporary for test file
    _cursor_logo.setTextureRect(sf::IntRect(0,0,30,30));
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_cursor_logo);
}