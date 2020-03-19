#pragma once

#include "Constants.h"
#include "Arithmetic.h"

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
	return multOf(diameter, PI);
}

float diamOfCircum(float circumference)
{
	return divOf(circumference, PI);
}

float areaCircle(float radius)
{
	return multOf(PI, power(radius, 2));
}

float volumeOfRectPrism(float length, float width, float heigth)
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

float volumeOfTriangularPrism(float base, float heigth, float length)
{
	return (base * heigth * length) / 2.0f;
}

float volumeOfCylinder(float radius, float heigth)
{
	return (PI * power(radius, 2) * heigth);
}

float volumeOfPyramide(float length, float width, float heigth)
{
	return (length * width * heigth) / 3.0f;
}

float volumeOfCone(float radius, float heigth)
{
	return (PI * power(radius, 2) * heigth) / 3.0f;
}

float volumeOfSphere(float radius)
{
	return (4.0f * PI * power(radius, 3)) / 3.0f;
}

float pythagoreanTheorem(float a, float b)
{
	return

}