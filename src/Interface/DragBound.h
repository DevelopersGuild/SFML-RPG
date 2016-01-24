#ifndef TINS_INTERFACE_DRAGBOUND
#define TINS_INTERFACE_DRAGBOUND

#include "Bound.h"
#include "InterfaceEvent.h"
/*
A boundary that is able to be dragged by mouse.
*/
class DragBound : 
	public Bound, 
	public InterfaceEvent
{
private:
	sf::Vector2f mouse_previous;
	bool selected;
public:
	DragBound();
	DragBound(const sf::Vector2f& size);
	virtual ~DragBound();
	virtual void processEvent(const sf::RenderWindow& window, const sf::Event& event) override;
};
#endif