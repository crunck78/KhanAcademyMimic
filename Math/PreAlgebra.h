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
protected:
	std::map<unsigned long long int, unsigned short int> m_decomposeValues; // holds a map of m_Wholenumber decomposition, key-values are the place values, and element-values are the digits coresponding to m_WhloeNumber's place-value
	std::vector<unsigned long long int> m_expandValues; //holds the expand-values of m_WholeNumber after decomposition ( expand-value equals key-value * coresponding element-value of m_decomposeValues )
	std::map<unsigned long long int, unsigned long long int> m_factorPairs; //holds a map of factors after defactorisation, key-values and element-value are the pair factors of m_WholeNumber that compose it
	unsigned long long int m_WholeNumber;// 18446744073709551615; // maximal value
public:

	WholeNumber()
		:m_WholeNumber(MIN_WHOLE_NUM)
	{
		
	}

	WholeNumber(const unsigned long long int number)
	{
		set(number);
	}

	virtual void set(const unsigned long long int number)
	{
		if (number > MAX_WHOLE_NUM)
			m_WholeNumber = MAX_WHOLE_NUM;
		else
			m_WholeNumber = number;
		m_clear();
	}

	const unsigned long long int getWholeNumber() const
	{
		return m_WholeNumber;
	}

	const std::vector<unsigned long long int>::reverse_iterator getExpandValuesRbegin()
	{
		const std::vector<unsigned long long int>::reverse_iterator rbegin = m_expandValues.rbegin();
		return rbegin;
	}

	const std::vector<unsigned long long int>::reverse_iterator getExpandValuesRend()
	{
		const std::vector<unsigned long long int>::reverse_iterator rend = m_expandValues.rend();
		return rend;
	}

	const std::map<unsigned long long int, unsigned short int>::reverse_iterator getDecomposeValuesRbegin()
	{
		const std::map<unsigned long long int, unsigned short int>::reverse_iterator rBegin = m_decomposeValues.rbegin();
		return rBegin;
	}

	const std::map<unsigned long long int, unsigned short int>::reverse_iterator getDecomposeValuesRend()
	{
		const std::map<unsigned long long int, unsigned short int>::reverse_iterator rEnd = m_decomposeValues.rend();
		return rEnd;
	}
	
	const std::map<unsigned long long int, unsigned long long int>::reverse_iterator getFactorsRbegin()
	{
		const std::map<unsigned long long int, unsigned long long int>::reverse_iterator rBegin = m_factorPairs.rbegin();
		return rBegin;
	}

	const std::map<unsigned long long int, unsigned long long int>::reverse_iterator getFactorsRend()
	{
		const std::map<unsigned long long int, unsigned long long int>::reverse_iterator rEnd = m_factorPairs.rend();
		return rEnd;
	}

	const unsigned long long int getRoundingTo(const unsigned long long int nearstRounding) const // 1000000000000000000 max nearst rounding value,  10 min nearsts rounding
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

	//it is a mess
	void decompose()
	{
		unsigned long long int temp = m_WholeNumber; //holds the left-side trunc to be evaluated
		unsigned long long int placeValue = 1; //holds the place-value to get from temp

		if (m_WholeNumber < BASE_10)
		{
			m_expandValues.push_back(m_WholeNumber);
			m_decomposeValues[placeValue] = m_WholeNumber;
		}
		else // get every expand-value and decomposed-value untile last place-value
		{
			while (temp >= BASE_10)
			{
				m_decomposeValues[placeValue] = (temp % BASE_10);
				m_expandValues.push_back((temp % BASE_10) * (placeValue)); //get last digit of temp place-value
				temp = temp / BASE_10; // next left-side trunc, trow the last digit out
				placeValue *= BASE_10;// next place value
			}
			m_decomposeValues[placeValue] = temp;
			m_expandValues.push_back((temp) * (placeValue));//last case, last place-value does not get evaluated, cus temp at this point will be less then BASE_10 ( being the last digit )
		}
	}

	void defactorise()
	{
		const int c_firstFactor = 1;
		const int c_noMatch = 0;

		if(m_WholeNumber == MIN_WHOLE_NUM || m_WholeNumber == c_firstFactor)
			m_factorPairs[m_WholeNumber] = m_WholeNumber;
		else
		{
			unsigned long long int divTest = c_firstFactor;
			while (m_factorPairs.count(divTest) == c_noMatch)
			{
				if (m_isDivisible(divTest))
				{
					m_factorPairs[m_WholeNumber / divTest] = divTest;
				}	
				divTest++;
			}
		}
	}

protected:
	void m_clear()
	{
		if (!m_expandValues.empty())
			m_expandValues.clear();

		if (!m_factorPairs.empty())
			m_factorPairs.clear();
	}

private:
	bool m_isDivisible(unsigned long long int divisor)
	{
		return (m_WholeNumber % divisor) == MIN_WHOLE_NUM;
	}
};

class Integer: public WholeNumber
{
protected:
	long long int m_Integer;

public:

	Integer()
		:m_Integer(MIN_WHOLE_NUM)
	{

	}

	Integer(long long int number)
	{
		set(number);
	}

	virtual void set(long long int number)
	{
		if (number > MAX_INT)
			m_Integer = MAX_INT;
		else if(number < MIN_INT)
			m_Integer = MIN_INT;
		else
			m_Integer = number;
		m_WholeNumber = getAbsoluteValue();
		m_clear();
	}

	const long long int getInteger() const
	{
		return m_Integer;
	}

	const long long int getOpposite() const
	{
		return (MIN_WHOLE_NUM - m_Integer);
	}

	const unsigned long long int getAbsoluteValue() const
	{
		if (m_Integer < MIN_WHOLE_NUM)
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
		set(num, den);
	}

	void set(long long int num, long long int den)
	{
		if (den == MIN_WHOLE_NUM)
			std::cout << "Denominator can not equal 0!" << std::endl;
		else
		{
			m_Numerator.set(num);
			m_Denominator.set(den);
			m_Rational = (long double)m_Numerator.getInteger() / (long double)m_Denominator.getInteger();
			m_Integer = (long long int)m_Rational;
			m_WholeNumber = getAbsoluteValue();
			m_clear();
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