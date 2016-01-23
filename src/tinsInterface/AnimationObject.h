#ifndef TINS_INTERFACE_ANIMATIONOBJECT
#define TINS_INTERFACE_ANIMATIONOBJECT

#include <SFML/Graphics.hpp>

/*
AnimationObject is a base class that makes the Interface Object able to
do smooth movement.
*/
class AnimationObject
{
private:
	sf::Clock m_clock;
	sf::Vector2f destination;
	sf::Time m_durationTime;
protected:


public:
	AnimationObject();
	virtual ~AnimationObject();
	enum AnimationType{ Accelerating, Decelerating, Regular };

	/*
	Set the object animates to the destination within n seconds with
	particular AnimationType
	*/
	virtual void animateTo(const sf::Vector2f destination, const sf::Time& seconds, AnimationType type) = 0;

	/*
	Update the object position in new frame.
	*/
	virtual void animateUpdate() = 0;
};
#endif