#include "AnimationObject.h"

AnimationObject::AnimationObject() :
m_destination(0,0),
m_velocity(0,0),
m_acceleration(0,0),
isAction(false)
{

}

AnimationObject::~AnimationObject()
{

}

void AnimationObject::animateTo(sf::Vector2f destination, sf::Time time, AnimationObject::Style style)
{
	m_destination = destination;
	isAction = true;
	sf::Vector2f start = animation_getPosition();
	if (style == Style::Regularly)
	{
		m_velocity.x = (destination.x - start.x) / time.asSeconds();
		m_velocity.y = (destination.y - start.y) / time.asSeconds();
		m_clock.restart();
	}
	else if (style == Style::Decelerating)
	{
		m_velocity.x = (destination.x - start.x) * 2;
		m_velocity.y = (destination.y - start.y) * 2;
		m_velocity.x = m_velocity.x / time.asSeconds();
		m_velocity.y = m_velocity.y / time.asSeconds();
		m_acceleration.x = -m_velocity.x / time.asSeconds();
		m_acceleration.y = -m_velocity.y / time.asSeconds();
		m_clock.restart();
	}
	else if (style == Style::Accelerating)
	{
		m_velocity.x = 0;
		m_velocity.y = 0;
		m_acceleration.x = ((destination.x - start.x) * 2) / (time.asSeconds() * (time.asSeconds()));
		m_acceleration.y = ((destination.y - start.y) * 2) / (time.asSeconds() * (time.asSeconds()));
		m_clock.restart();
	}
}

void AnimationObject::animateUpdate()
{
	sf::Time deltaTime = m_clock.getElapsedTime();
	sf::Vector2f delta(0, 0);

	if (deltaTime > sf::seconds(0.005f))
	{
		delta.x = m_velocity.x * deltaTime.asSeconds();
		delta.y = m_velocity.y * deltaTime.asSeconds();

		m_velocity.x += m_acceleration.x * deltaTime.asSeconds();
		m_velocity.y += m_acceleration.y * deltaTime.asSeconds();

		m_clock.restart();
	}

	if (m_isExcess(animation_getPosition(), delta))
	{
		animation_setPosition(m_destination);
		stopAnimation();
	}

	animation_Move(delta);
}

bool AnimationObject::m_isExcess(sf::Vector2f currentPoint, sf::Vector2f displacement)
{
	sf::Vector2f distance = m_destination - currentPoint;
	//absoulte math
	if (distance.x < 0)
	{
		distance.x = -distance.x;
	}
	if (distance.y < 0)
	{
		distance.y = -distance.y;
	}
	if (displacement.x < 0)
	{
		displacement.x = -displacement.x;
	}
	if (displacement.y < 0)
	{
		displacement.y = -displacement.y;
	}
	sf::Vector2f remain = distance - displacement;
	if (remain.x < 0 || remain.y < 0)
	{
		return true;
	}
	return false;
}

void AnimationObject::stopAnimation()
{
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	isAction = false;
}