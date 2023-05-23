#include "Rectangle.h"

#include <corecrt_math_defines.h>
#include <cmath>

rectangle::rectangle()
{
	// Set vertices to the default point value.
	topLeft = point();
	topRight = point();
	bottomLeft = point();
	bottomRight = point();
}

rectangle::rectangle(const point& inTopLeft, const point& inTopRight, const point& inBottomLeft, const point& inBottomRight)
{
	// Set vertices to the points that have been passed into the function.
	topLeft = inTopLeft;
	topRight = inTopRight;
	bottomLeft = inBottomLeft;
	bottomRight = inBottomRight;
}

float rectangle::getWidth() const
{
	// Return the distance between the top left and top right vertices.
	return topLeft.getDistance(topRight);
}

float rectangle::getHeight() const
{
	// Return the distance between the top left and bottom left vertices.
	return topLeft.getDistance(bottomLeft);
}

point rectangle::getCenter() const
{
	// Calculate the sum of the vertices and divide it by 4.
	return (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;
}

float rectangle::getArea() const
{
	// Multiply the width and height of the rectangle to get the area.
	return getWidth() * getHeight();
}

void rectangle::rotateRectangle(const point& centerPoint, const float angleDegrees)
{
	// Covert the angle from degrees to radians.
	float angleRadians = (angleDegrees * M_PI) / 180.0f;

	// Create an array of the vertices.
	std::vector<point> rectangleVertices = { topLeft, topRight, bottomLeft, bottomRight };

	// Create an array to hold the rotated vertices and reserve the required space.
	std::vector<point> rotatedRectangleVertices;
	rotatedRectangleVertices.reserve(rectangleVertices.size());

	// Iterate through all the vertices in the rectangle.
	for (const point& vertex : rectangleVertices)
	{
		// Calculate the point relative to the center point.
		point translatedPoint = vertex - centerPoint;

		// Get the sin and cos of the angle.
		float sinResult = sin(angleRadians);
		float cosResult = cos(angleRadians);

		// Calculate the rotated vertex and push this back into the array we set up earlier.
		point rotatedVertex = point(translatedPoint.x * cosResult - translatedPoint.y * sinResult, translatedPoint.x * sinResult + translatedPoint.y * cosResult);
		rotatedRectangleVertices.push_back(rotatedVertex + centerPoint);
	}

	// Set our rectangle vertices to the appropriate values.
	topLeft = rotatedRectangleVertices[0];
	topRight = rotatedRectangleVertices[1];
	bottomLeft = rotatedRectangleVertices[2];
	bottomRight = rotatedRectangleVertices[3];
}

bool rectangle::areRectangleVerticesInsidePolygon(const std::vector<point>& polygonPoints) const
{
	// Check that all the vertices lye inside the polygon.
	return topLeft.isPointInsidePolygon(polygonPoints) && topRight.isPointInsidePolygon(polygonPoints)
		&& bottomLeft.isPointInsidePolygon(polygonPoints) && bottomRight.isPointInsidePolygon(polygonPoints);
}

bool rectangle::operator==(const rectangle& other) const
{
	// Check that all of the vertices match between the two rectangles.
	return topLeft == other.topLeft && topRight == other.topRight
		&& bottomLeft == other.bottomLeft && bottomRight == other.bottomRight;
}

bool rectangle::operator>(const rectangle& other) const
{
	// Compare the area of both the rectangles.
	return getArea() > other.getArea();
}