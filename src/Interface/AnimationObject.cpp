#include "AnimationObject.h"
#include <iostream>

AnimationObject::AnimationObject() :
m_destination(0, 0),
m_velocity(0, 0),
m_acceleration(0, 0),
m_isAction(false),
m_opacity_current(255),
m_opacity_final(255),
m_opacity_speed(0),
m_isChangingOpacity(false)
{

}

AnimationObject::~AnimationObject()
{

}

void AnimationObject::animateTo(sf::Vector2f destination, sf::Time time, AnimationObject::Style style)
{
	m_destination = destination;
	m_isAction = true;
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
	float opacity_change = 0;	//don't change this. If this is an int, it will always be 0!

	if (deltaTime > sf::seconds(0.005f))
	{
		//update the position
		delta.x = m_velocity.x * deltaTime.asSeconds();
		delta.y = m_velocity.y * deltaTime.asSeconds();

		m_velocity.x += m_acceleration.x * deltaTime.asSeconds();
		m_velocity.y += m_acceleration.y * deltaTime.asSeconds();

		//update the opacity
		opacity_change = m_opacity_speed * deltaTime.asSeconds();
		m_clock.restart();
	}

	if (m_isAction)
	{
		if (m_isExcess(animation_getPosition(), delta))
		{
			animation_setPosition(m_destination);
			stopAnimation();
		}
		else
		{
			animation_Move(delta);
		}
	}

	if (m_isChangingOpacity)
	{
		if (m_isExcess(m_opacity_current, opacity_change))
		{
			m_opacity_current = m_opacity_final;
			setOpacity(m_opacity_current);
			stopOpacityAnimation();
		}
		else
		{
			m_opacity_current += opacity_change;
			setOpacity(m_opacity_current);
		}
	}
}

bool AnimationObject::m_isExcess(sf::Vector2f currentPoint, sf::Vector2f displacement)
{
	sf::Vector2f distance = m_destination - currentPoint;
	//absoulte math
	if (distance.x < 0)
		distance.x = -distance.x;
	if (distance.y < 0)
		distance.y = -distance.y;
	if (displacement.x < 0)
		displacement.x = -displacement.x;
	if (displacement.y < 0)
		displacement.y = -displacement.y;
	sf::Vector2f remain = distance - displacement;
	if (remain.x < 0 || remain.y < 0)
	{
		return true;
	}
	return false;
}

void AnimationObject::animateOpacityTo(int newOpacity, sf::Time time)
{
	if (newOpacity >= 0 && newOpacity <= 255)
	{
		m_opacity_speed = (newOpacity - m_opacity_current) / time.asSeconds();
		m_opacity_final = newOpacity;
		m_isChangingOpacity = true;
		m_clock.restart();
	}
}

bool AnimationObject::m_isExcess(int currentOpacity, int OpacityChanged)
{
	int distance = m_opacity_final - m_opacity_current;
	if (distance < 0)
		distance = -distance;
	if (OpacityChanged < 0)
		OpacityChanged = -OpacityChanged;

	int remain = distance - OpacityChanged;
	if (remain <= 0)
	{
		return true;
	}
	return false;
}

void AnimationObject::stopAnimation()
{
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_isAction = false;
}

void AnimationObject::stopOpacityAnimation()
{
	m_opacity_speed = 0;
	m_isChangingOpacity = false;
}