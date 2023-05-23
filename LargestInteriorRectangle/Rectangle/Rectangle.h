#pragma once

#include "../Point/Point.h"

#include <vector>

// Rectangle structure to hold the 4 vertices of a rectangle and any functions that will be required for the rectangle.
struct Rectangle
{
	// Variable to hold the top left vertex of this rectangle.
	Point topLeft;

	// Variable to hold the top right vertex of this rectangle.
	Point topRight;

	// Variable to hold the bottom left vertex of this rectangle.
	Point bottomLeft;

	// Variable to hold the bottom right vertex of this rectangle.
	Point bottomRight;

	// Default constructor.
	Rectangle();

	// Overloaded constructor.
	Rectangle(const Point& inTopLeft, const Point& inTopRight, const Point& inBottomLeft, const Point& inBottomRight);

	// Function to return the width of the rectangle.
	float getWidth() const;

	// Function to return the height of the rectangle.
	float getHeight() const;

	// Function to return the center point of the rectangle.
	Point getCenter() const;

	// Function to return the area of the rectangle.
	float getArea() const;

	// Function to rotate the rectangle around a specified center point.
	void rotateRectangle(const Point& centerPoint, const float angleDegrees = 1.0f);

	// Function to check if all the rectangles verices lye inside a specified polygon.
	bool areRectangleVerticesInsidePolygon(const std::vector<Point>& polygonPoints) const;

	// Operator override function to allow us to check if one rectangle equals another.
	bool operator==(const Rectangle& other) const;

	// Operator override function to allow us to check if one rectangle is greater than another.
	bool operator>(const Rectangle& other) const;
};