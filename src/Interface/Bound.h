#ifndef TINS_INTERFACE_BOUND
#define TINS_INTERFACE_BOUND

#include "AnimationObject.h"

/*
An invisible, animationable boundary 
*/
class Bound : 
	public AnimationObject, 
	public sf::Drawable,	//debug
	public sf::Rect<float>
{
private:
	//define how to get the bound's position
	sf::Vector2f animation_getPosition() override
	{ 
		return sf::Vector2f(left, top); 
	}

	//define how the bound moves
	void animation_Move(sf::Vector2f displacement) override 
	{
		left += displacement.x; 
		top += displacement.y; 
	}

	//define how to set the object's position
	void animation_setPosition(sf::Vector2f position) override 
	{
		left = position.x; 
		top = position.y; 
	}

public:
	Bound();
	Bound(const sf::Vector2f& newSize);
	virtual ~Bound();

	/*
	Set the size of the boundary
	*/
	void setSize(const sf::Vector2f& size);

	/*
	get the size of the boundary
	*/
	sf::Vector2f getSize(){ return sf::Vector2f(width,height); }

	/*
	set the position of the boundary
	*/
	void setPosition(sf::Vector2f position){ animation_setPosition(position); }

	/*
	move the position of the boundary
	*/
	void move(sf::Vector2f displacement){ animation_Move(displacement); }

	/*
	get the position of the boundary
	*/
	sf::Vector2f getPosition(){ return animation_getPosition(); }
	/*
	Debug: Draw the boundary on screen
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif