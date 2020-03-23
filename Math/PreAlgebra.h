#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#define MIN_WHOLE_NUMER_VALUE		 0
#define BASE_10						 10
#define MAX_ROUNDING				 1000000000000000000
#define MIN_ROUNDING								  10
#define MAX_WHOLE_NUM_VALUE			 9223372036854775807 //18446744073709551615
#define MAX_INT_VALUE				 9223372036854775807
#define MIN_INT_VALUE				-9223372036854775808

class WholeNumber
{
private:
	std::vector<unsigned long long int> m_placeValues; //holds the place values
	unsigned long long int m_WholeNumber;// 18446744073709551615; // maximal value
public:

	WholeNumber()
		:m_WholeNumber(0)
	{

	}

	WholeNumber(unsigned long long int number)
	{
		setWholeNumber(number);
	}

	virtual void setWholeNumber(unsigned long long int number)
	{
		if (number > MAX_WHOLE_NUM_VALUE)
			m_WholeNumber = MAX_WHOLE_NUM_VALUE;
		else
			m_WholeNumber = number;

		if(!m_placeValues.empty())
			m_placeValues.clear();

		m_decomposeWholeNumber();
	}

	unsigned long long int getWholeNumber()
	{
		return m_WholeNumber;
	}

	unsigned long long int getPlaceValues(int index)
	{
		return m_placeValues[index];
	}

	int getPlaceValuesSize()
	{
		return m_placeValues.size();
	}

	unsigned long long int getRoundingTo( unsigned long long int nearstRounding) //1000000000000000000 max nearst rounding value
	{
		const unsigned long long int roundingPoint = (nearstRounding / 2); // if above rounding point round up, else round down
		const int roundUp = 1;
		const int roundDown = 0;

		if (m_WholeNumber == nearstRounding)
			return m_WholeNumber;
		if (m_WholeNumber < nearstRounding)
		{
			if (m_WholeNumber < roundingPoint)
				return roundDown;
			return nearstRounding; //roundUp;
		}

		unsigned long long int leftTrunc = m_WholeNumber / nearstRounding; //holds the leftside trunc to be rounded
		unsigned long long int rigthTrunc = m_WholeNumber % nearstRounding; //holds the rightside trunc to be evaluated

		if (rigthTrunc < roundingPoint)
			return (leftTrunc * nearstRounding); //roundDown
		return (leftTrunc + roundUp) * nearstRounding; //roundUp
	}

/*
	Regrouping whole numbers
*/
	void regroupAs()
	{
		//TODO
	}

private:
	//it is a mess
	void m_decomposeWholeNumber()
	{
		if (m_WholeNumber < BASE_10)
		{
			m_placeValues.push_back(m_WholeNumber);
		}
		else // get every place value untile last case
		{
			unsigned long long int temp = m_WholeNumber; //holds the left-side trunc to be evaluated
			unsigned long long int placeValue = 1; //holds the place-value to get from temp

			while (temp >= BASE_10)
			{
				m_placeValues.push_back((temp % BASE_10) * (placeValue)); //get last digit of temp place-value
				temp = temp / BASE_10; // next left-side trunc, trow the last digit out
				placeValue *= BASE_10;// next place value
			}
			m_placeValues.push_back((temp) * (placeValue));//last case, last place-value does not get evaluated, cus temp at this point will be less then BASE_10 ( being the last digit )
		}
	}
};

class Integer
{
private:
	long long int m_Integer;

public:

	Integer()
		:m_Integer(0)
	{

	}

	Integer(long long int number)
		:m_Integer(number)
	{
	
	}

	void setInteger(long long int number)
	{
		m_Integer = number;
	}

	long long int getInteger()
	{
		return m_Integer;
	}

	long long int getOpposite()
	{
		return (MIN_WHOLE_NUMER_VALUE - m_Integer);
	}

	long long int getAbsoluteValue()
	{
		if (m_Integer < MIN_WHOLE_NUMER_VALUE)
			return getOpposite();
		return m_Integer;
	}
};

class RationalNumber
{
private:
	Integer m_Numerator;
	Integer m_Denominator; // can not be equal to zero
	long double m_Rational;
public:
	RationalNumber(long long int num, long long int den)
	{
		m_Numerator.setInteger(num);
		m_Denominator.setInteger(den);
		m_Rational = (long double)(m_Numerator.getInteger() / m_Denominator.getInteger());
	}

	/*RationalNumber(long double rational)
	{
		//TODO check if rational
	}*/


};

class IrrationalNumber
{
private:
	long double m_Irrational;
public:
	IrrationalNumber(long double irr)
	{
		//TODO check if irrational
	}
};

/*
- Order of Operations

*/

/*
- Arithmetic Properties
	Commutative property of multiplication
	Associative Property of multiplication
	Identity property of multiplication

	Commutative property of addition
	Associative Property of addition
	Identity property of addition
*/

/*
- Distributive property
*/

/*
- Factors and multiples
*/