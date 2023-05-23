#include "Test.h"
#include "../Polygon/PolygonAlgorithms.h"

#include <iostream>

// Create an array of points to be used for testing.
const std::vector<point> testPolygon = { point(0.0f, 0.0f), point(2.3f, 2.7f), point(4.1f, 1.9f), point(6.4f, 3.2f), point(8.9f, 1.5f), point(10.2f, 4.6f),
										 point(9.7f, 7.3f), point(12.8f, 6.4f), point(14.5f, 8.2f), point(12.7f, 10.9f), point(14.3f, 12.1f), point(11.9f, 14.4f), point(9.6f, 12.8f),
										 point(6.2f, 14.9f), point(5.4f, 12.3f), point(2.6f, 13.7f), point(1.1f, 10.6f), point(3.9f, 8.5f), point(1.3f, 6.1f), point(3.7f, 4.3f) };

void simplifyPolygonTest()
{
	// Variable to hold the simplified polygon.
	std::vector<point> simplifiedTestPolygon;

	// Call simplify polygon function from the polygon algorithms library.
	simplifyPolygon(testPolygon, simplifiedTestPolygon);

	// Output test polygon points to the console.
	std::cout << "Test Polygon" << "\n";
	std::cout << "------------" << "\n";

	for (const point& testPolygonPoint : testPolygon)
	{
		std::cout << "(" << testPolygonPoint.x << ", " << testPolygonPoint.y << "), ";
	}

	std::cout << "\n\n";

	// Output simplified polygon points to the console.
	std::cout << "Simplified Polygon" << "\n";
	std::cout << "------------------" << "\n";

	for (const point& simplifiedPolygonPoint : simplifiedTestPolygon)
	{
		std::cout << "(" << simplifiedPolygonPoint.x << ", " << simplifiedPolygonPoint.y << "), ";
	}

	std::cout << "\n\n";
}

void calculateLargestInteriorRectangleTest()
{
	// Variable to hold the largest interior rectangle.
	rectangle largestInterioRectangle = calculateLargestInteriorRectangle(testPolygon);

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
	rectangle largestInterioRectangle = calculateLargestInteriorRectangleWithAngleSweep(testPolygon);

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