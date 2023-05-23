#pragma once

#include "../Point/Point.h"

#include <vector>

// Rectangle structure to hold the 4 vertices of a rectangle and any functions that will be required for the rectangle.
struct rectangle
{
	// Variable to hold the top left vertex of this rectangle.
	point topLeft;

	// Variable to hold the top right vertex of this rectangle.
	point topRight;

	// Variable to hold the bottom left vertex of this rectangle.
	point bottomLeft;

	// Variable to hold the bottom right vertex of this rectangle.
	point bottomRight;

	// Default constructor.
	rectangle();

	// Overloaded constructor.
	rectangle(const point& inTopLeft, const point& inTopRight, const point& inBottomLeft, const point& inBottomRight);

	// Function to return the width of the rectangle.
	float getWidth() const;

	// Function to return the height of the rectangle.
	float getHeight() const;

	// Function to return the center point of the rectangle.
	point getCenter() const;

	// Function to return the area of the rectangle.
	float getArea() const;

	// Function to rotate the rectangle around a specified center point.
	void rotateRectangle(const point& centerPoint, const float angleDegrees = 1.0f);

	// Function to check if all the rectangles verices lye inside a specified polygon.
	bool areRectangleVerticesInsidePolygon(const std::vector<point>& polygonPoints) const;

	// Operator override function to allow us to check if one rectangle equals another.
	bool operator==(const rectangle& other) const;

	// Operator override function to allow us to check if one rectangle is greater than another.
	bool operator>(const rectangle& other) const;
};