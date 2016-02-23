#ifndef TINS_INTERFACE_SLOT
#define TINS_INTERFACE_SLOT
/*
A slot puts dragBounds to its slot if the dragBound is within the slot area.
*/
#include "DragBound.h"
#include <functional>

class Slot : public Bound, public InterfaceEvent
{
private:
    std::function<void()> onHover;  //what to do when the mouse is on the slot boundary?
    std::function<void()> onRelease;    //what to do when the mouse release?
public:
    Slot();
    void processEvent(const sf::RenderWindow& window, const sf::Event& event);
};
#endif
