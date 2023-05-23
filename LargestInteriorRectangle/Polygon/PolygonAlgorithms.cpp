#include "PolygonAlgorithms.h"

#include <corecrt_math_defines.h>
#include <cmath>
#include <algorithm>
#include <future>

std::vector<Point> PolygonAlgorithms::getRotatedPolygon(const std::vector<Point>& polygonPoints, const Point& centerPoint, float angleDegrees)
{
	// Conver angle from degrees to radians.
	float angleRadians = (angleDegrees * M_PI) / 180.0f;

	// Create an array to hold the vertices of the rotated polygon and reserve the desired size.
	std::vector<Point> rotatedPolygonPoints;
	rotatedPolygonPoints.reserve(polygonPoints.size());

	// Loop through all the vertices of the polygon.
	for (const Point& vertex : polygonPoints)
	{
		// Make the vertex relative to the center point.
		Point translatedPoint = vertex - centerPoint;

		// Get the sin and cos of the angle.
		float sinResult = sin(angleRadians);
		float cosResult = cos(angleRadians);

		// Create the rotated vertex and push it back into the array we created before.
		Point rotatedVertex = Point(translatedPoint.x * cosResult - translatedPoint.y * sinResult, translatedPoint.x * sinResult + translatedPoint.y * cosResult);
		rotatedPolygonPoints.push_back(rotatedVertex + centerPoint);
	}

	// Return the array of rotated polygon vertices.
	return rotatedPolygonPoints;
}

float PolygonAlgorithms::getPerpendicularDistance(const Point& targetPoint, const Point& lineStart, const Point& lineEnd)
{
	float dX = lineEnd.x - lineStart.x;
	float dY = lineEnd.y - lineStart.y;

	const float mag = pow(pow(dX, 2.0) + pow(dY, 2.0), 0.5);
	if (mag > 0.0)
	{
		dX /= mag;
		dY /= mag;
	}

	const float pvX = targetPoint.x - lineStart.x;
	const float pvY = targetPoint.y - lineStart.y;

	const float pvDot = dX * pvX + dY * pvY;

	const float dsX = pvDot * dX;
	const float dsY = pvDot * dY;

	const float aX = pvX - dsX;
	const float aY = pvY - dsY;

	return pow(pow(aX, 2.0) + pow(aY, 2.0), 0.5);
}

void PolygonAlgorithms::simplifyPolygon(const std::vector<Point>& polygonPoints, std::vector<Point>& outSimplifiedPolygonPoints, const float epsilon)
{
	if (polygonPoints.size() < 2)
	{
		return;
	}

	float dMax = 0.0;
	int index = 0;
	int endIndex = polygonPoints.size() - 1;
	for (int pointIndex = 1; pointIndex < endIndex; pointIndex++)
	{
		float distance = getPerpendicularDistance(polygonPoints[pointIndex], polygonPoints[0], polygonPoints[endIndex]);
		if (distance > dMax)
		{
			index = pointIndex;
			dMax = distance;
		}
	}

	if (dMax > epsilon)
	{
		std::vector<Point> recordedResults1;
		std::vector<Point> recordedResults2;
		std::vector<Point> firstLine(polygonPoints.begin(), polygonPoints.begin() + index + 1);
		std::vector<Point> lastLine(polygonPoints.begin() + index, polygonPoints.end());
		simplifyPolygon(firstLine, recordedResults1, epsilon);
		simplifyPolygon(lastLine, recordedResults2, epsilon);

		outSimplifiedPolygonPoints.assign(recordedResults1.begin(), recordedResults1.end() - 1);
		outSimplifiedPolygonPoints.insert(outSimplifiedPolygonPoints.end(), recordedResults2.begin(), recordedResults2.end());

		if (outSimplifiedPolygonPoints.size() < 2)
		{
			return;
		}
	}
	else
	{
		outSimplifiedPolygonPoints.clear();
		outSimplifiedPolygonPoints.push_back(polygonPoints[0]);
		outSimplifiedPolygonPoints.push_back(polygonPoints[endIndex]);
	}
}

void PolygonAlgorithms::calculateInteriorRectangles(const std::vector<Point>& polygonPoints, std::vector<Rectangle>& outRectangles, std::vector<bool>& outInternalRectangles, int& outGridHeight, int& outGridWidth)
{
	// Create arrays to hold all the unique x and y positions.
	std::vector<float> xPositions;
	std::vector<float> yPositions;

	// Loop through all the vertices of the polygon.
	for (int pointIndex = 0; pointIndex < polygonPoints.size(); pointIndex++)
	{
		// Push the x and y positions back into the arrays.
		xPositions.push_back(polygonPoints[pointIndex].x);
		yPositions.push_back(polygonPoints[pointIndex].y);
	}

	// Remove all duplicates from the arrays and resize them accordingly.
	std::vector<float>::iterator it = std::unique(xPositions.begin(), xPositions.end());
	xPositions.resize(std::distance(xPositions.begin(), it));

	it = std::unique(yPositions.begin(), yPositions.end());
	yPositions.resize(std::distance(yPositions.begin(), it));

	// Sort the arrays from lowest to highest value.
	sort(xPositions.begin(), xPositions.end());
	sort(yPositions.begin(), yPositions.end());

	// Create an array to hold all the intersections.
	std::vector<Point> intersections;

	// Loop through all the x and y positions.
	for (int xPositionIndex = 0; xPositionIndex < xPositions.size(); xPositionIndex++)
	{
		for (int yPositionIndex = 0; yPositionIndex < yPositions.size(); yPositionIndex++)
		{
			// Add the intersection to the array.
			intersections.push_back(Point(xPositions[xPositionIndex], yPositions[yPositionIndex]));
		}
	}

	// Set the grid width and height.
	outGridWidth = xPositions.size();
	outGridHeight = yPositions.size();

	// Loop through all the intersections that can be used as the bottom left vertex of a rectangle.
	for (int intersectionIndex = 0; intersectionIndex < intersections.size() - (outGridWidth + 1); intersectionIndex++)
	{
		// Create a rectangle and push it back into the array of rectangles.
		Rectangle currentRectangle(intersections[intersectionIndex + outGridWidth], intersections[intersectionIndex + 1 + outGridWidth], intersections[intersectionIndex], intersections[intersectionIndex + 1]);
		outRectangles.push_back(currentRectangle);

		// Check if all the vertices of the rectangle lye inside the polygon.
		if (currentRectangle.areRectangleVerticesInsidePolygon(polygonPoints))
		{
			outInternalRectangles.push_back(true);
		}
		else
		{
			outInternalRectangles.push_back(false);
		}
	}
}

Rectangle PolygonAlgorithms::calculateLargestInteriorRectangle(const std::vector<Point>& polygonPoints)
{
	// Setup variables for the calculate interior rectangles function.
	std::vector<Rectangle> rectangles;
	std::vector<bool> internalRectangles;
	int gridWidth;
	int gridHeight;

	// Get all the interior rectangles as well as the grid width and height.
	calculateInteriorRectangles(polygonPoints, rectangles, internalRectangles, gridHeight, gridWidth);

	// Create a variable to hold the largest rectangle.
	Rectangle largestRectangle;

	// Loop through all the internal rectangles.
	for (int internalRectangleIndex = 0; internalRectangleIndex < internalRectangles.size(); internalRectangleIndex++)
	{
		// If the rectangle doesn't lye inside the polygon then move onto the next iteration of the loop.
		if (!internalRectangles[internalRectangleIndex])
		{
			continue;
		}

		// Setup variables for iteration on the rectangles.
		int xSpan = INT16_MAX;
		int ySpan = -1;
		int topLeftRectangle = internalRectangleIndex;

		// While the specified rectangle is ture,
		while (internalRectangles[topLeftRectangle])
		{
			// Check if we are in range.
			if (topLeftRectangle < internalRectangles.size())
			{
				// Create a variable for the current x span of this rectangle.
				int currentXSpan = 0;

				// Loop through the array from the current position to a max of grid width along the X axis.
				for (int horizontalRectangleIndex = 1; horizontalRectangleIndex < gridWidth; horizontalRectangleIndex++)
				{
					// If this rectangle is withing the polygon and we are on the same row as the top left rectangle.
					if (internalRectangles[topLeftRectangle + horizontalRectangleIndex] && (topLeftRectangle % gridWidth) + horizontalRectangleIndex < gridWidth)
					{
						// Increment the span.
						currentXSpan++;
					}
					else
					{
						// If not then break out of this iteration.
						break;
					}
				}

				// Compare the current and stored x span.
				if (currentXSpan < xSpan)
				{
					// Set the x span to equal the current x span.
					xSpan = currentXSpan;
				}

				// Increment the y span and move the top left rectangle up in the grid.
				ySpan++;
				topLeftRectangle += gridWidth;
			}
			else
			{
				// If we aren't in range then break out of the loop.
				break;
			}
		}

		// Check if the rectangle spans more than one rectangle in the grid.
		if (ySpan > 0 && xSpan > 0)
		{
			// Create variables for a rectangle.
			Point topLeft = rectangles[internalRectangleIndex + (ySpan * gridWidth)].topLeft;
			Point topRight = rectangles[internalRectangleIndex + xSpan + (ySpan * gridWidth)].topRight;
			Point bottomLeft = rectangles[internalRectangleIndex].bottomLeft;
			Point bottomRight = rectangles[internalRectangleIndex + xSpan].bottomRight;
			Rectangle currentRectangle(topLeft, topRight, bottomLeft, bottomRight);

			// Compare the current rectangle to the largest rectangle so far and if the current has a larger aarea set it to be the largest.
			if (currentRectangle > largestRectangle)
			{
				largestRectangle = currentRectangle;
			}
		}
	}

	// Return the largest rectangle found.
	return largestRectangle;
}

Rectangle PolygonAlgorithms::calculateLargestInteriorRectangleWithAngleSweep(const std::vector<Point>& polygonPoints, const float deltaRotation, const int numberOfThreads)
{
	// Calculate the sum of all the points.
	Point pointsSum;
	for (const Point& pointValue : polygonPoints)
	{
		pointsSum = pointsSum + pointValue;
	}

	// Get the center point (average) of the polygon.
	Point centerPoint = pointsSum / polygonPoints.size();

	// Calculate the number of rotations needed based on the delta rotation.
	int numberOfRotations = 89 / deltaRotation;

	// Create a variable to hold the largest rectangle found.
	Rectangle largestInteriorRectangle;

	// Check if we wish to multi-thread.
	if (numberOfThreads > 1)
	{
		// Create an array of futures.
		std::vector<std::future<Rectangle>> futures;

		// Loop based on how many threads we wish to use.
		for (int threadIndex = 0; threadIndex < numberOfThreads; threadIndex++)
		{
			// Determine the start and end index for each thread.
			const int startIndex = threadIndex * numberOfRotations / numberOfThreads;
			const int endIndex = (threadIndex + 1) * numberOfRotations / numberOfThreads;

			// Call the calculate largest interior rectangle with angle sweep task asynchronously and push that into the array of futures.
			futures.push_back(std::async(calculateLargestInteriorRectangleWithAngleSweepTask, polygonPoints, deltaRotation, startIndex, endIndex, centerPoint));
		}

		// Create an array to hold the rectangles found from the futures.
		std::vector<Rectangle> rectangles;

		// Iterate through all the futures.
		for (int futureIndex = 0; futureIndex < futures.size(); futureIndex++)
		{
			// Add the rectangle found by the future to the rectangles array.
			rectangles.push_back(futures[futureIndex].get());

			// If the rectangle found is larger than the largest rectangle then set the largest to be the rectangle we just found.
			if (rectangles[futureIndex] > largestInteriorRectangle)
			{
				largestInteriorRectangle = rectangles[futureIndex];
			}
		}
	}
	else
	{
		// If we do not wish to multi-thread this function then call the task with start index as 0 and end index as the number of rotations.
		largestInteriorRectangle = calculateLargestInteriorRectangleWithAngleSweepTask(polygonPoints, deltaRotation, 0, numberOfRotations, centerPoint);
	}

	// Return the largest rectangle found.
	return largestInteriorRectangle;
}

Rectangle PolygonAlgorithms::calculateLargestInteriorRectangleWithAngleSweepTask(const std::vector<Point>& polygonPoints, const float deltaRotation, const int startIndex, const int endIndex, const Point& centerPoint)
{
	// Create variables to be used in iteration.
	std::vector<Point> rotatedPolygonPoints;
	Rectangle largestInteriorRectangle;
	Rectangle currentRectangle;

	// Loop from start to end index.
	for (int currentIndex = startIndex; currentIndex < endIndex; currentIndex++)
	{
		// Rotate the polygon by the desired rotation at this iteration.
		rotatedPolygonPoints = getRotatedPolygon(polygonPoints, centerPoint, currentIndex * deltaRotation);

		// Get the largest interior rectangle of that polygon.
		currentRectangle = calculateLargestInteriorRectangle(rotatedPolygonPoints);

		// Check if the current rectangle is greater than the largest rectangle previously found.
		if (currentRectangle > largestInteriorRectangle)
		{
			// Rotate the rectangle to be non-axis-aligned.
			currentRectangle.rotateRectangle(centerPoint, -(currentIndex * deltaRotation));

			// Set the largest rectangle to be the current rectangle.
			largestInteriorRectangle = currentRectangle;
		}
	}

	// Return the largest rectangle found.
	return largestInteriorRectangle;
}