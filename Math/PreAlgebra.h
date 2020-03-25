#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <math.h>
#include "Constants.h"
#include "Arithmetic.h"


class WholeNumber
{
private:
	std::vector<unsigned long long int> m_placeValues; //holds the place values after decomposition
	std::map<unsigned long long int, unsigned long long int> m_factors; //holds a map of factors after defactorisation
	unsigned long long int m_WholeNumber;// 18446744073709551615; // maximal value
public:

	WholeNumber()
		:m_WholeNumber(0)
	{

	}

	WholeNumber(const unsigned long long int number)
	{
		setWholeNumber(number);
	}

	void setWholeNumber(const unsigned long long int number)
	{
		if (number > MAX_WHOLE_NUM_VALUE)
			m_WholeNumber = MAX_WHOLE_NUM_VALUE;
		else
			m_WholeNumber = number;

		if(!m_placeValues.empty())
			m_placeValues.clear();

		if (!m_factors.empty())
			m_factors.clear();

		m_decomposeWholeNumber();
		m_defactoriseWholeNumber();
	}

	const unsigned long long int getWholeNumber() const
	{
		return m_WholeNumber;
	}

	const std::vector<unsigned long long int>::iterator getPlaceValuesBegin()
	{
		const std::vector<unsigned long long int>::iterator begin = m_placeValues.begin();
		return begin;
	}

	const std::vector<unsigned long long int>::iterator getPlaceValuesEnd()
	{
		const std::vector<unsigned long long int>::iterator end = m_placeValues.begin();
		return end;
	}
	
	const std::map<unsigned long long int, unsigned long long int>::reverse_iterator getFactorsRbegin()
	{
		const std::map<unsigned long long int, unsigned long long int>::reverse_iterator rBegin = m_factors.rbegin();
		return rBegin;
	}

	const std::map<unsigned long long int, unsigned long long int>::reverse_iterator getFactorsRend()
	{
		const std::map<unsigned long long int, unsigned long long int>::reverse_iterator rEnd = m_factors.rend();
		return rEnd;
	}

	const unsigned long long int getRoundingTo(const unsigned long long int nearstRounding) const //1000000000000000000 max nearst rounding value
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

	void m_defactoriseWholeNumber()
	{
		if(m_WholeNumber == MIN_WHOLE_NUMER_VALUE || m_WholeNumber == 1)
			m_factors[m_WholeNumber] = m_WholeNumber;
		else
		{
			unsigned long long int divTest = 1;
			while (m_factors.count(divTest) == 0)
			{
				if (isDivisible(m_WholeNumber, divTest))
				{
					m_factors[m_WholeNumber / divTest] = divTest;
				}	
				divTest++;
			}
		}
	}
};

class Integer: public WholeNumber
{
private:
	long long int m_Integer;

public:

	Integer()
		:m_Integer(0)
	{

	}

	Integer(long long int number)
	{
		setInteger(number);
	}

	void setInteger(long long int number)
	{
		m_Integer = number;
		setWholeNumber(getAbsoluteValue());
	}

	const long long int getInteger() const
	{
		return m_Integer;
	}

	const long long int getOpposite() const
	{
		return (MIN_WHOLE_NUMER_VALUE - m_Integer);
	}

	const unsigned long long int getAbsoluteValue() const
	{
		if (m_Integer < MIN_WHOLE_NUMER_VALUE)
			return (unsigned long long int)getOpposite();
		return (unsigned long long int)m_Integer;
	}
};

class RationalNumber: public Integer
{
private:
	Integer m_Numerator;
	Integer m_Denominator; // can not be equal to zero
	long double m_Rational;
public:
	RationalNumber(long long int num, long long int den)
	{
		setNumAndDenom(num, den);
	}

	void setNumAndDenom(long long int num, long long int den)
	{
		if (den == 0)
		{
			std::cout << "Denominator can not equal 0!" << std::endl;
		}
		else
		{
			m_Numerator.setInteger(num);
			m_Denominator.setInteger(den);
			m_Rational = (long double)m_Numerator.getInteger() / (long double)m_Denominator.getInteger();
			setInteger((long long int)m_Rational);
		}
	}

	const Integer getNumerator() const
	{
		return m_Numerator;
	}

	const Integer getDenominator() const
	{
		return m_Numerator;
	}

	const long double getRatio() const
	{
		return m_Rational;
	}
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