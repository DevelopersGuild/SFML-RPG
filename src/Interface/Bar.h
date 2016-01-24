#ifndef TINS_INTERFACE_BAR
#define TINS_INTERFACE_BAR

#include "Bound.h"
/*
A simple bar that can be used as progress bar or hp bar.
Included bar animation.
*/
class Bar : public Bound
{
private:
	float m_percentage;
	float m_speed;
	float m_acceleration;
	float m_finalPercentage;
	sf::Clock m_clock;

	sf::Color m_color_rightTop;
	sf::Color m_color_rightBottom;
	sf::Color m_color_leftTop;
	sf::Color m_color_leftBottom;
public:
	Bar();
	Bar(const sf::Color& color);
	Bar(const sf::Color& rightTop, const sf::Color& rightBottom,
		const sf::Color& leftTop, const sf::Color& leftBottom);

	virtual ~Bar();

	//set the color of the bar
	void setColor(const sf::Color& color);

	//set the color at each corner of the bar, the bar will try to mix the colors
	void setColor(const sf::Color& rightTop, const sf::Color& rightBottom,
				  const sf::Color& leftTop, const sf::Color& leftBottom);

	//change the bar percentage to a new percentage in 1-second-animation
	void setBarAnimation(float finalPercent);

	//update the bar percentage during animation
	void barAnimationUpdate();

	//set the percentage of the bar (0 - 1.0)
	void setPercentage(float percent){ if(percent <= 1 && percent >= 0) m_percentage = percent; }

	//draw the bar on the screen
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//get the percentage of the bar
	float getPercent(){ return m_percentage; }
};
#endif