#ifndef TINS_INTERFACE_BOUND
#define TINS_INTERFACE_BOUND

#include "AnimationObject.h"

/*
An invisible, animationable boundary 
*/
class Bound : 
	public AnimationObject, 
	public sf::Rect<float>,
	public sf::Drawable	//debug
{
private:

public:
	Bound();
	Bound(const sf::Vector2f& size);
	virtual ~Bound();

	/*
	Set the size of the boundary
	*/
	void setSize(const sf::Vector2f& size);

	/*
	Make the Boundary animate to particular location within certain 
	time and AnimationType
	*/
	void animateTo(const sf::Vector2f destination, const sf::Time& seconds, AnimationType type);

	/*
	Update the boundary per frame
	*/
	void animateUpdate();

	/*
	Debug: Draw the boundary on screen
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif