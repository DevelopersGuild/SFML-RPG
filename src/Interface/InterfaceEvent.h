#ifndef TINS_INTERFACE_INTERFACE_EVENT
#define TINS_INTERFACE_INTERFACE_EVENT

#include <SFML/Graphics.hpp>
/*
A base class that identify the interface Object can process Events
*/
class InterfaceEvent
{
public:
	virtual void processEvent(const sf::RenderWindow& window, const sf::Event& event) = 0;
};
#endif