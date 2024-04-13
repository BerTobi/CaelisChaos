#ifndef TMATH_H
#define TMATH_H

#define PI 3.14159265

#include <iostream>
#include <string>

struct Point
{
	float x;
	float y;
};


inline float cDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline float cDistance(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

#endif