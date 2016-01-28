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
class Cursor
{
private:
	sf::Sprite cursor_logo;	//the picture of the cursor
	DragBound* ptrDrag;		//a pointer to the dragBound, NULL when no dragBound is selected
	sf::RenderWindow& window;	//the window that the cursor belongs to
	sf::Vector2f position;	//the position of the mouse
public:
	Cursor();			//load the set of cursor textures
	Cursor(const sf::RenderWindow& window);		//bind the cursor to window

	enum State{ default, loading, clicking };	//the state of the mouse
	void setState(State state);		//change the mouse's logo by changing its state

	sf::Vector2f getPosition();		//get the position of the cursor in the window
	void update();					//update the position of the cursor
};
#endif