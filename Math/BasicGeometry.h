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

	void init(float x, float y)
	{
		setX(x);
		setY(y);
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

	void rotate(Point2d center, float angle)
	{
		//TODO
	}

	void reflectOver(float reflectionLineSlope)
	{
		//TODO 
		/*
		-find point of perpendicular intersection
			-
		*/
	}
};

class Line{

private:
	Point2d m_endPoints[2];
	Point2d m_midPoint;
	float m_slope; 
	float m_length;
	
public:
	//constructor rework need
	Line(Point2d endPoint1 = 0.0f, Point2d endPoint2 = 0.0f)
	{
		m_endPoints[0] = endPoint1;
		m_endPoints[1] = endPoint2;
		m_setMidPoint();
		m_setLength();
		m_setSlope();
	}

	void setEndPoint(Point2d point, int index)
	{
		//TODO guard against invalid index
		m_endPoints[index] = point;
		m_setMidPoint();
		m_setLength();
		m_setSlope();
	}

	Point2d getEndPoint(int index)
	{
		//TODO guard against invalid index
		return m_points[index];
	}

	Point2d getMidPoint()
	{
		return m_midPoint;
	}

	float getLength()
	{
		return m_length;
	}

	float getSlope()
	{
		return m_slope;
	}

	void translate( float x, float y )
	{
		m_endPoints[0].translate(x, y);
		m_endPoints[1].translate(x, y);
		m_midPoint.translate(x, y);
	}

	void rotate(Point2d center, float angle)
	{
		//TODO



		m_setSlope();
	}

private:

	void m_setLength()
	{
		m_length = m_points[0].getDistanceFrom(m_points[1]);
	}

	void m_setMidPoint()
	{
		//TODO
	}

	void m_setSlope()
	{
		//TOD
	}
};

class Triangle{
	
private:
	/*
	*	line[0] is the base, angle[0] is oppose to base,
	*	angle[1] is oppose to line[1], angle[2] is oppose to line[2]
	*/
	Line m_lines[3];
	Point2d heigth; // point oppose to base;
	float m_area;
	float m_angle[3];
	float m_perimeter;

public:
	// constructor parameters rework need
	Triangle(Line base = 0.0f, Point2d heigth = 0.0f)
	{
		m_lines[0] = base;
		m_lines[1].setEndPoint(m_lines[0].getEndPoint(0));
		m_lines[1].setEndPoint(height);
		m_lines[2].setEndPoint(m_lines[0].getEndPoint(1));
		m_lines[2].setEndPoint(height);
	}

	void translate( float x, float y )
	{
		line[0].translate( x, y );
		line[1].translate( x, y );
		line[2].translate( x, y );
	}

	void rotate(Point2d center, float angle)
	{
		//TODO
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
