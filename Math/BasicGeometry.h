#pragma once

#include "Constants.h"
#include "Arithmetic.h"
#include <math.h>

class Point2d
{
	
private:
	long double m_x;
	long double m_y;
	
public:
	Point2d()
		: m_x(0), m_y(0) {}

	Point2d(const long double x, const long double y)
		: m_x(x), m_y(y) {}

	Point2d(const Point2d &other)
	{
		this->init(other.m_x, other.m_y);
	}

	Point2d& operator=(const Point2d &other)
	{
		if(this != &other)
			this->init(other.m_x, other.m_y);
		return *this;
	}

	void init(const long double x, const long double y)
	{
		setX(x);
		setY(y);
	}

	void setX(const long double x)
	{
		m_x = x;
	}

	void setY(const long double y)
	{
		m_y = y;
	}

	const long double getX() const 
	{
		return m_x;
	}
	
	const long double getY() const 
	{
		return m_y;
	}

	const long double getDistanceFrom(const Point2d &other)
	{
		return hypot( (other.getX() - m_x), (other.getY() - m_y));
	}

	const Point2d getMidPointFrom(const Point2d& other) const
	{
		Point2d midPoint;
		midPoint.setX(midValue(this->m_x, other.m_x));
		midPoint.setY(midValue(this->m_y, other.m_y));
		return midPoint;
	}
	
	void translate( const long double x, const long double y )
	{
		m_x += x;
		m_y += y;
	}

	void rotate(const Point2d& center, const long double angle)
	{
		//TODO
	}

	void reflectOver(const long double reflectionLineSlope)
	{
		//TODO 
		/*
		-find point of perpendicular intersection
			-
		*/
	}
};

class Segment{

private:
	Point2d m_endPoints[2], m_midPoint;
	long double m_rise, m_run, m_slope, m_length;
	bool m_isVertical, m_isHorizontal;
	
public:
	//constructor rework need
	Segment()
	{
		m_endPoints[0].init(-0.5f, 0.0f);
		m_endPoints[1].init(0.5f, 0.0f);
		m_setLength();
		m_setSlope();
		m_setMidPoint();
	}

	Segment(const long double endPoint1[], const long double endPoint2[])
	{
		m_endPoints[0].init(endPoint1[0], endPoint1[1]);
		m_endPoints[1].init(endPoint2[0], endPoint2[1]);
		m_setLength();
		m_setSlope();
		m_setMidPoint();
	}

	Segment(const Point2d& endPoint1, const Point2d& endPoint2)
	{
		m_endPoints[0] = endPoint1;
		m_endPoints[1] = endPoint2;
		m_setLength();
		m_setSlope();
		m_setMidPoint();
	}

	void setEndPoint(const Point2d point, const int index)
	{
		//TODO guard against invalid index
		m_endPoints[index] = point;
		m_setLength();
		m_setSlope();
		m_setMidPoint();
	}

	const Point2d getEndPoint(const int index) const
	{
		//TODO guard against invalid index
		return m_endPoints[index];
	}

	const Point2d getMidPoint() const
	{
		return m_midPoint;
	}

	const long double getLength() const
	{
		return m_length;
	}

	const long double getSlope() const
	{
		return m_slope;
	}

	const long double getRise() const 
	{
		return m_rise;
	}

	const long double getRun() const 
	{
		return m_run;
	}

	const Point2d getintersectingPoint(const Point2d &other)
	{
		//TODO
	}

	void translate( const long double x, const long double y )
	{
		m_endPoints[0].translate(x, y);
		m_endPoints[1].translate(x, y);
		m_midPoint.translate(x, y);
	}

	void rotate(const Point2d &center, const long double angle)
	{
		//TODO
		m_setSlope();
	}

	bool isVertical()
	{
		return (m_run == NULL) && (m_rise != 0.0f);
	}

	bool isHorizontal()
	{
		return (m_rise == 0.0f) && (m_run != NULL);
	}

	bool isPerpendicular(const Segment &other)
	{
		//TODO
	}

	bool isParallel(const Segment &other)
	{
		//TODO
	}
private:

	void m_setLength()
	{
		m_length = m_endPoints[0].getDistanceFrom(m_endPoints[1]);
	}

	void m_setMidPoint()
	{
		m_midPoint.setX(midValue(m_endPoints[0].getX(), m_endPoints[1].getX()));
		m_midPoint.setY(midValue(m_endPoints[0].getY(), m_endPoints[1].getY()));
	}

	void m_setSlope()
	{
		m_setRise();
		m_setRun();
		if (isVertical())
			m_slope = NULL; 
		else
			m_slope = m_rise / m_run;
	}

	void m_setRun()
	{
		m_run = (m_endPoints[0].getX() - m_endPoints[1].getX());
	}

	void m_setRise()
	{
		m_rise = (m_endPoints[0].getY() - m_endPoints[1].getY());
	}
};

class Triangle{
	
private:
	/* CONVENTION
	*	Segment[0] is the base,
	*	angle[0], point[0] is oppose to Segment[0],
	*	angle[1], point[1] is oppose to Segment[1],
	*	angle[2], point[2] is oppose to Segment[2]
	*/
	Segment m_Sides[3];
	long double m_angles[3];
	long double m_perimeter, m_area;

public:
	// constructor parameters rework need
	Triangle(const Point2d endPoints[3])
	{
		m_Sides[0].setEndPoint(endPoints[1], 0); //Segment0, endPoint1
		m_Sides[0].setEndPoint(endPoints[2], 1); //Segment0, endPoint2
		m_Sides[1].setEndPoint(endPoints[1], 0); //Segment 1, endPoint1
		m_Sides[1].setEndPoint(endPoints[0], 1); //Segment1, endPoint0 ( height )
		m_Sides[2].setEndPoint(endPoints[2], 0); //Segment2 , endPoint2
		m_Sides[2].setEndPoint(endPoints[0], 1); //Segment2, endPoint0 ( height )
	}

	Triangle(const Segment &base, const Point2d &heigth)
	{
		m_Sides[0] = base;
		m_Sides[1].setEndPoint(m_Sides[0].getEndPoint(0), 0); 
		m_Sides[1].setEndPoint(heigth, 1);
		m_Sides[2].setEndPoint(m_Sides[0].getEndPoint(1), 0);
		m_Sides[2].setEndPoint(heigth, 1);
	}

	const long double getArea() const
	{
		//TOdO
	}

	const long double getPerimeter() const
	{
		//TOdO
	}

	void translate( long double x, long double y )
	{
		m_Sides[0].translate( x, y );
		m_Sides[1].translate( x, y );
		m_Sides[2].translate( x, y );
	}

	void rotate(Point2d center, long double angle)
	{
		//TODO
	}

	//Classifying triangles by their angles

	bool isAcute()
	{
		//TODO

	}

	bool isRight()
	{
		//TODO
	}

	bool isObtuse()
	{
		//TODO
	}

	//Classifying triangles by their side lengths
	bool isEquilateral()
	{
		//TODO
	}

	bool isIsosceles()
	{
		//TODO
	}

	bool isScalene()
	{
		//TODO
	}
};

long double areaRect(long double length, long double heigth)
{
	return (length * heigth);
}

long double areaTriangle(long double base, long double heigth)
{
	return (areaRect(base, heigth) / 2.0f);
}

long double circumOfDiam(long double diameter)
{
	return (diameter * PI);
}

long double diamOfCircum(long double circumference)
{
	return (circumference / PI);
}

long double areaCircle(long double radius)
{
	return (PI * pow(radius, 2));
}

long double volumeOfRectPrism(long double length, long double width, long double heigth)
{
	return(length * width * heigth);
}

long double areaOfRectPrism(long double length1, long double length2, long double length3)
{
	long double sidesArea = areaRect(length1, length2) * 2.0f;
	long double topBottomArea = areaRect(length1, length3) * 2.0f;
	long double frontBackArea = areaRect(length2, length3) * 2.0f;

	return (sidesArea + topBottomArea + frontBackArea);
}

long double volumeOfTriangularPrism(long double base, long double heigth, long double length)
{
	return (base * heigth * length) / 2.0f;
}

long double volumeOfCylinder(long double radius, long double heigth)
{
	return (PI * pow(radius, 2) * heigth);
}

long double volumeOfPyramide(long double length, long double width, long double heigth)
{
	return (length * width * heigth) / 3.0f;
}

long double volumeOfCone(long double radius, long double heigth)
{
	return (PI * pow(radius, 2) * heigth) / 3.0f;
}

long double volumeOfSphere(long double radius)
{
	return (4.0f * PI * pow(radius, 3) / 3.0f);
}
