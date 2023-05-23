#pragma once

#include "../Rectangle/Rectangle.h"

#include <vector>

namespace PolygonAlgorithms
{
	// Function to rotate a polygon by a specified angle clockwise.
	std::vector<Point> getRotatedPolygon(const std::vector<Point>& polygonPoints, const Point& centerPoint, float angleDegrees);

	// Function to return the perpendicular distance of a point.
	float getPerpendicularDistance(const Point& targetPoint, const Point& lineStart, const Point& lineEnd);

	// Function to simplify a polygon by removing unnecessary points. This utilizes the Ramer-Douglas-Peucker algorithm.
	void simplifyPolygon(const std::vector<Point>& polygonPoints, std::vector<Point>& outSimplifiedPolygonPoints, const float epsilon = 1.0f);

	// Function to calculate all rectangles inside a specified polygon and whether or not they lye inside the polygon.
	void calculateInteriorRectangles(const std::vector<Point>& polygonPoints, std::vector<Rectangle>& outRectangles, std::vector<bool>& outInternalRectangles, int& outGridHeight, int& outGridWidth);

	// Function to calculate the largest axis-aligned interior rectangle of a polygon.
	Rectangle calculateLargestInteriorRectangle(const std::vector<Point>& polygonPoints);

	// Function to calculate the largest non-axis-aligned interior rectangle of a polygon.
	Rectangle calculateLargestInteriorRectangleWithAngleSweep(const std::vector<Point>& polygonPoints, const float deltaRotation = 1.0f, const int numberOfThreads = 8);

	// Task to function to be fired off on separate threads when calling the above function.
	Rectangle calculateLargestInteriorRectangleWithAngleSweepTask(const std::vector<Point>& polygonPoints, const float deltaRotation, const int startIndex, const int endIndex, const Point& centerPoint);
}