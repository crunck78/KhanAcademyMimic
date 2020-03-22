#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#define BASE_10 10
#define MAX_ROUNDING 1000000000000000000
#define MIN_ROUNDING 10
#define MAX_VALUE 18446744073709551615

//ideas

/*
- Place Values
	Decompose whole numbers
*/
class WholeNumber
{
private:
	std::vector<unsigned long long int> m_placeValues; //holds the place values
	unsigned long long int m_number;// 18446744073709551615; // maximal value
public:
	WholeNumber(unsigned long long int number)
		:m_number(number)
	{
		m_decomposeWholeNumber();
	}
	void setWholeNumber(unsigned long long int number)
	{
		m_number = number;
		m_placeValues.clear();
		m_decomposeWholeNumber();
	}

	unsigned long long int getWholeNumber()
	{
		return m_number;
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
		const int roundingPoint = (nearstRounding / 2); // if above rounding point round up, else round down
		const int roundUp = 1;
		const int roundDown = 0;

		if (m_number == nearstRounding)
			return m_number;
		if (m_number < nearstRounding)
		{
			if (m_number < roundingPoint)
				return roundDown;
			return nearstRounding; //roundUp;
		}

		unsigned long long int leftTrunc = m_number / nearstRounding; //holds the leftside trunc to be rounded
		unsigned long long int rigthTrunc = m_number % nearstRounding; //holds the rightside trunc to be evaluated

		if (rigthTrunc < roundingPoint)
			return (leftTrunc * nearstRounding); //roundDown
		return (leftTrunc + roundUp) * nearstRounding; //roundUp
	}

private:
	//it is a mess
	void m_decomposeWholeNumber()
	{
		if (m_number < BASE_10)
		{
			m_placeValues.push_back(m_number);
		}
		else // get every place value untile last case
		{
			unsigned long long int temp = m_number; //holds the left-side trunc to be evaluated
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
/*
	Round whole numbers
	Regrouping whole numbers
*/



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
- Rational and irrational number
	Classifying numbers
*/

/*
- Factors and multiples
*/