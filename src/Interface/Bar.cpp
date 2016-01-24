#include "Bar.h"

Bar::Bar()
{
	m_percentage = 1;
	m_finalPercentage = 1;
	m_speed = 0;
	m_acceleration = 0;
	m_finalPercentage = width;
	setColor(sf::Color::White);
}

Bar::Bar(const sf::Color& color)
{
	m_percentage = 1;
	m_finalPercentage = 1;
	m_speed = 0;
	m_acceleration = 0;
	setColor(color);
}

Bar::Bar(const sf::Color& rightTop, const sf::Color& rightBottom,
	const sf::Color& leftTop, const sf::Color& leftBottom)
{
	m_percentage = 1;
	setColor(rightTop, rightBottom, leftTop, leftBottom);
}

void Bar::setColor(const sf::Color& color)
{
	m_color_rightTop = color;
	m_color_rightBottom = color;
	m_color_leftTop = color;
	m_color_leftBottom = color;
}

void Bar::setColor(const sf::Color& rightTop, const sf::Color& rightBottom,
	const sf::Color& leftTop, const sf::Color& leftBottom)
{
	m_color_rightTop = rightTop;
	m_color_rightBottom = rightBottom;
	m_color_leftTop = leftTop;
	m_color_leftBottom = leftBottom;
}

Bar::~Bar()
{

}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray vertex(sf::PrimitiveType::Quads, 4);
	vertex[0].position = sf::Vector2f(left, top);
	vertex[0].color = m_color_leftTop;
	vertex[1].position = sf::Vector2f(left + width * m_percentage, top);
	vertex[1].color = m_color_rightTop;
	vertex[2].position = sf::Vector2f(left + width * m_percentage, top + height);
	vertex[2].color = m_color_rightBottom;
	vertex[3].position = sf::Vector2f(left, top + height);
	vertex[3].color = m_color_leftBottom;
	target.draw(vertex, states);
}

void Bar::setBarAnimation(float finalPercent)
{
	if (finalPercent <= 1 && finalPercent >= 0)
	{
		m_finalPercentage = finalPercent;
		m_speed = (m_finalPercentage - m_percentage) * 2;
		m_acceleration = -m_speed;
		m_clock.restart();
	}
}

void Bar::barAnimationUpdate()
{
	sf::Time deltaTime = m_clock.getElapsedTime();
	float delta = 0;

	if (deltaTime > sf::seconds(0.005f))
	{
		delta = m_speed * deltaTime.asSeconds();;
		m_speed += m_acceleration * deltaTime.asSeconds();
		m_clock.restart();
	}

	float distance = m_finalPercentage - m_percentage;
	if (distance < 0)
	{
		distance = -distance;
	}
	float test = delta;
	if (test < 0)
	{
		test = -test;
	}

	if (test > distance)
	{
		m_percentage = m_finalPercentage;
		m_speed = 0;
		m_acceleration = 0;
	}
	else
	{
		m_percentage += delta;
	}
}