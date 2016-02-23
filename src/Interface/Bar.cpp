#include "Bar.h"

Bar::Bar()
{
	m_percentage = 1;
	m_finalPercentage = 1;
	m_speed = 0;
	m_acceleration = 0;
	m_finalPercentage = width;
	setColor(sf::Color::White);
	setOpacity(255);
}

Bar::Bar(const sf::Color& color)
{
	m_percentage = 1;
	m_finalPercentage = 1;
	m_speed = 0;
	m_acceleration = 0;
	setColor(color);
	setOpacity(255);
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
	int opacity = getOpacity();
	sf::Color temp1 = m_color_leftTop;
	temp1.a = opacity;
	sf::Color temp2 = m_color_rightTop;
	temp2.a = opacity;
	sf::Color temp3 = m_color_rightBottom;
	temp3.a = opacity;
	sf::Color temp4 = m_color_leftBottom;
	temp4.a = opacity;
	sf::VertexArray vertex(sf::PrimitiveType::Quads, 4);
	vertex[0].position = sf::Vector2f(left, top);
	vertex[0].color = temp1;
	vertex[1].position = sf::Vector2f(left + width * m_percentage, top);
	vertex[1].color = temp2;
	vertex[2].position = sf::Vector2f(left + width * m_percentage, top + height);
	vertex[2].color = temp3;
	vertex[3].position = sf::Vector2f(left, top + height);
	vertex[3].color = temp4;
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