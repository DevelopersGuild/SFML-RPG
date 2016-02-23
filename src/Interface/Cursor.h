#ifndef TINS_INTERFACE_CURSOR
#define TINS_INTERFACE_CURSOR

#include <SFML/Graphics.hpp>
#include "DragBound.h"

/*
The Cursor class provides utility supports to mouse event.
The cursor should be declare as static.
Load the set of textures of cursor when constructed,
and change the texture by changing its "States".
make it singleton?/ make it only exist in one class?...
*/
class Cursor: public InterfaceEvent, public sf::Drawable
{
public:
	Cursor();			//load the set of cursor textures
	Cursor(const sf::RenderWindow& window);		//bind the cursor to window

	enum State{ normal, loading, clicking };	//the state of the mouse
    void setState(Cursor::State state);		//change the mouse's logo by changing its state

	sf::Vector2f getPosition();		//get the position of the cursor in the window
    
    void processEvent(const sf::RenderWindow& window, const sf::Event& event);//update the cursor
    
    void loadTexture(const sf::Texture& texture);  //load and set the cursor texture
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite _cursor_logo;	//the picture of the cursor
    //DragBound* _ptrDrag;		//a pointer to the dragBound, NULL when no dragBound is selected
    const sf::RenderWindow* _window;	//the window that the cursor belongs to
    State _state;
};
#endif