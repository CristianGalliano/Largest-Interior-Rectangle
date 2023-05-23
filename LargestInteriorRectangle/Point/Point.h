#pragma once

#include <vector>

// Point structure to hold a 2D points x and y position as well as any functions that will be required.
struct Point
{
	// Variable to hold the x position of this 2D point.
	float x;

	// Variable to hold the y position of this 2D point.
	float y;

	// Default constructor.
	Point();

	// Overloaded constructor.
	Point(const float inX, const float inY);

	// Function to return the squared distance between this point and another.
	float getSquaredDistance(const Point& other) const;

	// Function to return this distance between this point and another.
	float getDistance(const Point& other) const;

	// Function to check if this point lies inside a polygon.
	bool isPointInsidePolygon(const std::vector<Point>& polygonPoints) const;

	// Operator override function to allow us to add another point to this point.
	Point operator+(const Point& other) const;

	// Operator override function to allow us to subtract another point from this point.
	Point operator-(const Point& other) const;

	// Operator override function to allow us to divide this point by a float.
	Point operator/(const float value) const;

	// Operator override function to allow us to check if one point equals another.
	bool operator==(const Point& other) const;
};