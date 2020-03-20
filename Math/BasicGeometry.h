#pragma once

#include "Constants.h"
#include <math.h>

class Point2d{
	
private:
	float m_x;
	float m_y;
	
public:

	Point2d(float x = 0, float y = 0)
		: m_x(x), m_y(y)
	{

	}

	void setX(float x)
	{
		m_x = x;
	}

	void setY(float y)
	{
		m_y = y;
	}

	float getX()
	{
		return m_x;
	}
	
	float getY()
	{
		return m_y;
	}

	//if no argument is provided it will return the distance from origin(0,0)
	float getDistanceFrom(Point2d other = 0.0f)
	{
		return hypot( (other.getX() - m_x), (other.getY() - m_y));
	}
	
	void translate( float x, float y )
	{
		m_x += x;
		m_y += y;
	}
};

class Line{

private:
	Point2d m_endPoint[2];
	float m_length;
	
public:
	Line(Point2d endPoint1 = 0.0f, Point2d endPoint2 = 0.0f)
	{
		m_endPoint[0] = endPoint1;
		m_endPoint[1] = endPoint2;
		m_length = m_endPoint[0].getDistanceFrom(m_endPoint[1]);
	}


	Point2d getEndPoint(int index)
	{
		//TODO guard against invalid index
		return m_endPoint[index];
	}

	Point2d getMidPoint()
	{

	}


	void translate( float x, float y )
	{
		m_endPoint[0].translate( x, y );
		m_endPoint[1].translate( x, y );
	}
};

struct Triangle{
	
	Line line[3];
	float area;
	float angle[3];
	float perimeter;
	
	void translate( float x, float y )
	{
		line[0].translate( x, y );
		line[1].translate( x, y );
		line[2].translate( x, y );
	}
};

float areaRect(float length, float heigth)
{
	return (length * heigth);
}

float areaTriangle(float base, float heigth)
{
	return (areaRect(base, heigth) / 2.0f);
}

float circumOfDiam(float diameter)
{
	return (diameter * PI);
}

float diamOfCircum(float circumference)
{
	return (circumference / PI);
}

float areaCircle(float radius)
{
	return (PI * pow(radius, 2));
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
	return (PI * pow(radius, 2) * heigth);
}

float volumeOfPyramide(float length, float width, float heigth)
{
	return (length * width * heigth) / 3.0f;
}

float volumeOfCone(float radius, float heigth)
{
	return (PI * pow(radius, 2) * heigth) / 3.0f;
}

float volumeOfSphere(float radius)
{
	return (4.0f * PI * pow(radius, 3) / 3.0f);
}
