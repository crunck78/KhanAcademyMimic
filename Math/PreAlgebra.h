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
	std::vector<unsigned long long int> m_primeFactors; // holds a vector of prime-factors
	unsigned long long int m_WholeNumber;// 9999999999999; // maximal value
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

	const std::vector<unsigned long long int> getPrimeFactors() const
	{
		return m_primeFactors;
	}

	const std::vector<unsigned long long int>::iterator getPrimeFactorsbegin()
	{
		const std::vector<unsigned long long int>::iterator begin = m_primeFactors.begin();
		return begin;
	}

	const std::vector<unsigned long long int>::iterator getPrimeFactorsend()
	{
		const std::vector<unsigned long long int>::iterator end = m_primeFactors.end();
		return end;
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

	const unsigned long long int getRoundingTo(const unsigned long long int nearstRounding) const // 100000000000 max nearst rounding value,  10 min nearsts rounding
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

	virtual void decompose()
	{
		if (m_decomposeValues.empty() && m_expandValues.empty()) // do decomposition
		{
			unsigned long long int temp = m_WholeNumber; //holds the left-side trunc to be evaluated
			unsigned long long int placeValue = 1; //holds the place-value to get from temp
			m_setDecomposeValue(temp, placeValue);
		}
		else
			std::cout << "Already decomposed!" << std::endl;
	}

	virtual void factorise()
	{
		if (m_WholeNumber != MIN_WHOLE_NUM) // can't factorise 0
		{
			if (m_factorPairs.empty() && m_primeFactors.empty()) // do factorization
			{
				unsigned long long int factorTest = 1;
				unsigned long long int factor = m_WholeNumber;
				unsigned long long int factorCounter = 1;
				do
				{
					if (m_WholeNumber % factorTest == 0) //found factor
						m_factorPairs[factorTest] = (m_WholeNumber / factorTest);
					factorTest++;// start prime factorization with 2
					while (factor % factorTest == 0)// found prime factor, 
					{
						m_primeFactors.push_back(factorTest);
						factor /= factorTest; //try get it again
						factorCounter *= factorTest; //all prime factors mutiply equals m_WholeNumber
					}
				} while (factorCounter != m_WholeNumber); // not find all prime factors
			}
			else
				std::cout << "Already factorized!" << std::endl;
		}
		else
			std::cout << "Can't factorise 0!" << std::endl;
	}

	const unsigned long long int getLCM(const unsigned long long int &number...) const
	{

	}

	//Regrouping whole numbers
	void regroupAs()
	{
		//TODO
	}

protected:
	void m_clear() // clear maps and vector members
	{
		if (! m_decomposeValues.empty())
			m_decomposeValues.clear();

		if (! m_expandValues.empty())
			m_expandValues.clear();

		if (! m_factorPairs.empty())
			m_factorPairs.clear();

		if (! m_primeFactors.empty())
			m_primeFactors.clear();
	}

private:
	bool m_isDivisible(unsigned long long int divisor)
	{
		return (m_WholeNumber % divisor) == MIN_WHOLE_NUM;
	}

	void m_setDecomposeValue(unsigned long long int &number, unsigned long long int &placeValue)
	{
		if (number < BASE_10) // last place-value
		{
			m_expandValues.push_back(number * placeValue);
			m_decomposeValues[placeValue] = number;
		}
		else // get every decomposed-value and expand-value  untile last place-value
		{
			m_decomposeValues[placeValue] = (number % BASE_10);
			m_expandValues.push_back((number % BASE_10) * (placeValue));
			m_setDecomposeValue((number /= BASE_10), (placeValue *= BASE_10)); // next decomposed- and expand-value
		}
	}

	//not done TODO
	void m_setFactorPair(unsigned long long int &factor, unsigned long long int &factorTest, unsigned long long int &factorCounter)
	{
		if (factorCounter == m_WholeNumber)
		{
			m_factorPairs[factorTest] = (m_WholeNumber / factorTest);
		}
		else
		{
			if (m_WholeNumber % factorTest == 0) //found factor
				m_factorPairs[factorTest] = (m_WholeNumber / factorTest);
			m_setPrimeFactor(factor, ++factorTest, factorCounter);// start prime factorization with 2
		}
	}

	//not done TODO
	void m_setPrimeFactor(unsigned long long int &factor, unsigned long long int &factorTest, unsigned long long int &factorCounter)
	{
		if(factor % factorTest == 0)// found prime factor, 
		{
			m_primeFactors.push_back(factorTest);
			m_setPrimeFactor((factor /= factorTest), factorTest, (factorCounter *= factorTest));
		}
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
		return m_Denominator;
	}

	const long double getRatio() const
	{
		return m_Rational;
	}

	void decompose()
	{
		m_Numerator.decompose();
		m_Denominator.decompose();
	}

	void factorise()
	{
		m_Numerator.factorise();
		m_Denominator.factorise();
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