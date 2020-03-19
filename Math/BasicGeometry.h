#pragma once

#include "Constants.h"

float areaRect(float length, float heigth)
{
	return multOf(length, heigth);
}

float areaTriangle(float base, float heigth)
{
	return divOf(areaRect(base, heigth), 2.0f);
}

float circumOfDiam(float diameter)
{
	return (diameter * PHI);
}

float diamOfCircum(float circumference)
{
	return (circumference / PHI);
}

float areaCircle(float radius)
{
	return (PHI * power(radius, 2));
}

float volumOfRectPrism(float length, float width, float heigth)
{
	return(length * width * heigth);
}

float areaOfRectPrism(float length1, float length2, float length3)
{
	float sidesArea = areaRect(length1, length2) * 2.0f;
	float topBottomArea = areaRect(length1, length3) * 2.0f;
	float frontBackArea = areaRect(length2, length3) * 2.0f;

	return (sidesArea + topBottomArea + frontBackArea);
}

float volumOfTriangularPrism(float base, float heigth, float length)
{
	return (base * heigth * length) / 2.0f;
}
