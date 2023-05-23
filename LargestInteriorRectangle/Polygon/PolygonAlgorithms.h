#pragma once

#include "../Rectangle/Rectangle.h"

#include <vector>

// Function to rotate a polygon by a specified angle clockwise.
std::vector<point> getRotatedPolygon(const std::vector<point>& polygonPoints, const point& centerPoint, float angleDegrees);

// Function to return the perpendicular distance of a point.
float getPerpendicularDistance(const point& targetPoint, const point& lineStart, const point& lineEnd);

// Function to simplify a polygon by removing unnecessary points. This utilizes the Ramer-Douglas-Peucker algorithm.
void simplifyPolygon(const std::vector<point>& polygonPoints, std::vector<point>& outSimplifiedPolygonPoints, const float epsilon = 1.0f);

// Function to calculate all rectangles inside a specified polygon and whether or not they lye inside the polygon.
void calculateInteriorRectangles(const std::vector<point>& polygonPoints, std::vector<rectangle>& outRectangles, std::vector<bool>& outInternalRectangles, int& outGridHeight, int& outGridWidth);

// Function to calculate the largest axis-aligned interior rectangle of a polygon.
rectangle calculateLargestInteriorRectangle(const std::vector<point>& polygonPoints);

// Function to calculate the largest non-axis-aligned interior rectangle of a polygon.
rectangle calculateLargestInteriorRectangleWithAngleSweep(const std::vector<point>& polygonPoints, const float deltaRotation = 1.0f, const int numberOfThreads = 8);

// Task to function to be fired off on separate threads when calling the above function.
rectangle calculateLargestInteriorRectangleWithAngleSweepTask(const std::vector<point>& polygonPoints, const float deltaRotation, const int startIndex, const int endIndex, const point& centerPoint);