#ifndef TINS_INTERFACE_ANIMATIONOBJECT
#define TINS_INTERFACE_ANIMATIONOBJECT

#include <SFML/Graphics.hpp>

/*
AnimationObject is a abstract base class that makes the Interface Object able to
do smooth movement.
Implement 
1.how to get the object's position in animation_getPosition(),
2.define how the object moves in animation_Move(sf::Vector2f displacement)
3.how to set the object's position in animation_setPosition(sf::Vector2f position) and
4.define how the object set its opacity
when inherit fromthis class.
*/

class AnimationObject : public sf::NonCopyable	//A moving object cannot be copied
{
private:
	sf::Clock m_clock;
	sf::Vector2f m_destination;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	bool m_isAction;	//is the object in animation?
	bool m_isChangingOpacity; //is the object changing the opacity?
	int m_opacity_current;
	int m_opacity_final;
	int m_opacity_speed;

	//check if the object goes beyond the destination after this displacement
	bool m_isExcess(sf::Vector2f currentPoint, sf::Vector2f displacement);
	
	//check if the object's opacity goes beyond the target value
	bool m_isExcess(int currentOpacity, int OpacityChanged);
protected:
	//define how to get the object's position for animation
	virtual sf::Vector2f animation_getPosition() = 0;
	//define how the object moves
	virtual void animation_Move(sf::Vector2f displacement) = 0;
	//define how to set the object's position
	virtual void animation_setPosition(sf::Vector2f position) = 0;
	//define how the object set its opacity
	virtual void setOpacity(int value){ m_opacity_current = value; }
public:
	AnimationObject();
	virtual ~AnimationObject();

	enum Style{ Accelerating, Decelerating, Regularly};

	/*
	Set the object animates to the destination within n seconds with particular Animation style
	*/
	void animateTo(sf::Vector2f destination, sf::Time seconds, AnimationObject::Style style);

	/*
	Set the object's opacity to particular value with n seconds
	*/
	void animateOpacityTo(int value, sf::Time seconds);

	/*
	get the opacity of the object
	*/
	int getOpacity() const { return m_opacity_current; } 

	/*
	Update the object position in the new frame.
	*/
	void animateUpdate();

	//stop the animation
	void stopAnimation();
	//stop the opacity animation
	void stopOpacityAnimation();

	//is the Object animating?
	bool isAnimating(){ return m_isAction; }

	//is the Object changing opacity?
	bool isChangingOpacity(){ return m_isChangingOpacity; }
};
#endif