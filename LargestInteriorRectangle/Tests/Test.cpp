#include "Test.h"
#include "../Polygon/PolygonAlgorithms.h"

#include <iostream>

// Create an array of points to be used for testing.
const std::vector<Point> testPolygon = { Point(0.0f, 0.0f), Point(2.3f, 2.7f), Point(4.1f, 1.9f), Point(6.4f, 3.2f), Point(8.9f, 1.5f), Point(10.2f, 4.6f),
										 Point(9.7f, 7.3f), Point(12.8f, 6.4f), Point(14.5f, 8.2f), Point(12.7f, 10.9f), Point(14.3f, 12.1f), Point(11.9f, 14.4f), Point(9.6f, 12.8f),
										 Point(6.2f, 14.9f), Point(5.4f, 12.3f), Point(2.6f, 13.7f), Point(1.1f, 10.6f), Point(3.9f, 8.5f), Point(1.3f, 6.1f), Point(3.7f, 4.3f) };

void simplifyPolygonTest()
{
	// Variable to hold the simplified polygon.
	std::vector<Point> simplifiedTestPolygon;

	// Call simplify polygon function from the polygon algorithms library.
	PolygonAlgorithms::simplifyPolygon(testPolygon, simplifiedTestPolygon);

	// Output test polygon points to the console.
	std::cout << "Test Polygon" << "\n";
	std::cout << "------------" << "\n";

	for (const Point& testPolygonPoint : testPolygon)
	{
		std::cout << "(" << testPolygonPoint.x << ", " << testPolygonPoint.y << "), ";
	}

	std::cout << "\n\n";

	// Output simplified polygon points to the console.
	std::cout << "Simplified Polygon" << "\n";
	std::cout << "------------------" << "\n";

	for (const Point& simplifiedPolygonPoint : simplifiedTestPolygon)
	{
		std::cout << "(" << simplifiedPolygonPoint.x << ", " << simplifiedPolygonPoint.y << "), ";
	}

	std::cout << "\n\n";
}

void calculateLargestInteriorRectangleTest()
{
	// Variable to hold the largest interior rectangle.
	Rectangle largestInterioRectangle = PolygonAlgorithms::calculateLargestInteriorRectangle(testPolygon);

	// Output the vertices and values of the largest interior rectangle to the console.
	std::cout << "Largest Interior Rectangle" << "\n";
	std::cout << "--------------------------" << "\n";
	std::cout << "Top Left Vertex: " << "(" << largestInterioRectangle.topLeft.x << ", " << largestInterioRectangle.topLeft.y << ")," << "\n";
	std::cout << "Top Right Vertex: " << "(" << largestInterioRectangle.topRight.x << ", " << largestInterioRectangle.topRight.y << ")," << "\n";
	std::cout << "Bottom Left Vertex: " << "(" << largestInterioRectangle.bottomLeft.x << ", " << largestInterioRectangle.bottomLeft.y << ")," << "\n";
	std::cout << "Bottom Right Vertex: " << "(" << largestInterioRectangle.bottomRight.x << ", " << largestInterioRectangle.bottomRight.y << ")," << "\n";
	std::cout << "Center: " << "(" << largestInterioRectangle.getCenter().x << ", " << largestInterioRectangle.getCenter().y << ")," << "\n";
	std::cout << "Width: " << largestInterioRectangle.getWidth() << "," << "\n";
	std::cout << "Height: " << largestInterioRectangle.getHeight() << "," << "\n";
	std::cout << "Area: " << largestInterioRectangle.getArea() << ".";

	std::cout << "\n\n";
}

void calculateLargestInteriorRectangleWithAngleSweepTest()
{
	// Variable to hold the largest interior rectangle.
	Rectangle largestInterioRectangle = PolygonAlgorithms::calculateLargestInteriorRectangleWithAngleSweep(testPolygon);

	// Output the vertices and values of the largest interior rectangle to the console.
	std::cout << "Largest Interior Rectangle With Angle Sweep" << "\n";
	std::cout << "-------------------------------------------" << "\n";
	std::cout << "Top Left Vertex: " << "(" << largestInterioRectangle.topLeft.x << ", " << largestInterioRectangle.topLeft.y << ")," << "\n";
	std::cout << "Top Right Vertex: " << "(" << largestInterioRectangle.topRight.x << ", " << largestInterioRectangle.topRight.y << ")," << "\n";
	std::cout << "Bottom Left Vertex: " << "(" << largestInterioRectangle.bottomLeft.x << ", " << largestInterioRectangle.bottomLeft.y << ")," << "\n";
	std::cout << "Bottom Right Vertex: " << "(" << largestInterioRectangle.bottomRight.x << ", " << largestInterioRectangle.bottomRight.y << ")," << "\n";
	std::cout << "Center: " << "(" << largestInterioRectangle.getCenter().x << ", " << largestInterioRectangle.getCenter().y << ")," << "\n";
	std::cout << "Width: " << largestInterioRectangle.getWidth() << "," << "\n";
	std::cout << "Height: " << largestInterioRectangle.getHeight() << "," << "\n";
	std::cout << "Area: " << largestInterioRectangle.getArea() << ".";

	std::cout << "\n\n";
}