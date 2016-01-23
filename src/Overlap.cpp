#include "Overlap.h"

bool overlap(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
	sf::FloatRect rectangle1 = sprite1.getGlobalBounds();
	sf::FloatRect rectangle2 = sprite2.getGlobalBounds();

	// Rectangles with negative dimensions are allowed, so we must handle them correctly
	// Compute the min and max of the first rectangle on both axes
	float r1MinX = std::min(rectangle1.left, rectangle1.left + rectangle1.width);
	float r1MaxX = std::max(rectangle1.left, rectangle1.left + rectangle1.width);
	float r1MinY = std::min(rectangle1.top, rectangle1.top + rectangle1.height);
	float r1MaxY = std::max(rectangle1.top, rectangle1.top + rectangle1.height);

	// Compute the min and max of the second rectangle on both axes
	float r2MinX = std::min(rectangle2.left, rectangle2.left + rectangle2.width);
	float r2MaxX = std::max(rectangle2.left, rectangle2.left + rectangle2.width);
	float r2MinY = std::min(rectangle2.top, rectangle2.top + rectangle2.height);
	float r2MaxY = std::max(rectangle2.top, rectangle2.top + rectangle2.height);

	// Compute the intersection boundaries
	float interLeft = std::max(r1MinX, r2MinX);
	float interTop = std::max(r1MinY, r2MinY);
	float interRight = std::min(r1MaxX, r2MaxX);
	float interBottom = std::min(r1MaxY, r2MaxY);

	// If the intersection is valid (positive non zero area), then there is an intersection
	return ((interLeft <= interRight) && (interTop <= interBottom));
}
