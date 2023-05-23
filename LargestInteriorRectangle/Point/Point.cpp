#include "Point.h"

#include <cmath>

point::point()
{
    // Set the x and y position of this point to 0.0f.
	x = 0.0f;
	y = 0.0f;
}

point::point(const float inX, const float inY)
{
    // Set the x and y position of this point to the passed in values.
	x = inX;
	y = inY;
}

float point::getSquaredDistance(const point& other) const
{
    // Calculate the squared distance using the usual algorithm.
	return pow((other.y - y), 2) + pow((other.x - x), 2);
}

float point::getDistance(const point& other) const
{
    // Get the square root of the square distance.
	return sqrt(getSquaredDistance(other));
}

bool point::isPointInsidePolygon(const std::vector<point>& polygonPoints) const
{
    int crossings = 0;
    int numVertices = polygonPoints.size();

    for (int pointIndex = 0; pointIndex < numVertices; ++pointIndex) 
    {
        const point& vertex1 = polygonPoints[pointIndex];
        const point& vertex2 = polygonPoints[(pointIndex + 1) % numVertices];

        if (((vertex1.y <= y) && (vertex2.y > y)) || ((vertex1.y > y) && (vertex2.y <= y)))
        {
            float vt = (y - vertex1.y) / (vertex2.y - vertex1.y);
            if (x < vertex1.x + vt * (vertex2.x - vertex1.x)) 
            {
                crossings++;
            }
        }
    }

    return (crossings % 2 == 1);
}

point point::operator+(const point& other) const
{
    // Add others x to this x and others y to this y.
	return point(x + other.x, y + other.y);
}

point point::operator-(const point& other) const
{
    // Minus others x from this x and others y from this y.
	return point(x - other.x, y - other.y);
}

point point::operator/(const float value) const
{
    // Divide both x and y by the passed in value.
	return point(x / value, y / value);
}

bool point::operator==(const point& other) const
{
    // Compare the x and y positions of both points.
	return x == other.x && y == other.y;
}