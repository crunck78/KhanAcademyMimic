#pragma once
#include <iostream>
//#include <utility>
#include <cstdarg>
#include <vector>
#include <map>
#include <math.h>
#include "Constants.h"
#include "Arithmetic.h"
#include "BasicGeometry.h"

class WholeNumber
{
protected:
	std::map<unsigned long long int, unsigned short int> m_decomposeValues; // holds a map of m_Wholenumber decomposition, key-values are the place values, and element-values are the digits coresponding to m_WhloeNumber's place-value
	std::vector<unsigned long long int> m_expandValues;						//holds the expand-values of m_WholeNumber after decomposition ( expand-value equals key-value * coresponding element-value of m_decomposeValues )
	std::map<unsigned long long int, unsigned long long int> m_factorPairs; //holds a map of factors after defactorisation, key-values and element-value are the pair factors of m_WholeNumber that compose it
	std::vector<unsigned long long int> m_primeFactors;						// holds a vector of prime-factors
	unsigned long long int m_WholeNumber;									// 9999999999999; // maximal value
public:
	WholeNumber()
		: m_WholeNumber(MIN_WHOLE_NUM) {}

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

	const std::vector<unsigned long long int> getExpandValues() const
	{
		return m_expandValues;
	}

	const std::vector<unsigned long long int>::iterator getPrimeFactorsbegin()
	{
		const std::vector<unsigned long long int>::iterator begin = m_primeFactors.begin();
		return begin;
	}

	const std::vector<unsigned long long int>::iterator getPrimeFactorsEnd()
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

	const std::map<unsigned long long int, unsigned long long int>::iterator getFactorsBegin()
	{
		const std::map<unsigned long long int, unsigned long long int>::iterator begin = m_factorPairs.begin();
		return begin;
	}

	const std::map<unsigned long long int, unsigned long long int>::iterator getFactorsEnd()
	{
		const std::map<unsigned long long int, unsigned long long int>::iterator end = m_factorPairs.end();
		return end;
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

		unsigned long long int leftTrunc = m_WholeNumber / nearstRounding;	//holds the leftside trunc to be rounded
		unsigned long long int rigthTrunc = m_WholeNumber % nearstRounding; //holds the rightside trunc to be evaluated

		if (rigthTrunc < roundingPoint)
			return (leftTrunc * nearstRounding);	   //roundDown
		return (leftTrunc + roundUp) * nearstRounding; //roundUp
	}

	virtual void decompose()
	{
		if (!(m_decomposeValues.empty() && m_expandValues.empty()))
			std::cout << "Already decomposed!" << std::endl;
		else // do decomposition
		{
			unsigned long long int temp = m_WholeNumber; //holds the left-side trunc to be evaluated
			unsigned long long int placeValue = 1;		 //holds the place-value to get from temp
			m_setDecomposeValue(temp, placeValue);
		}
	}

	virtual void factorise()
	{
		if (m_WholeNumber == MIN_WHOLE_NUM) // can't factorise 0
			std::cout << "Can't factorise 0!" << std::endl;
		else if (!m_factorPairs.empty())
			std::cout << "Already factorized!" << std::endl;
		else if (m_WholeNumber == MIN_FACTOR) //number equals 1
			m_factorPairs[MIN_FACTOR] = MIN_FACTOR;
		else // do factorization for number greater then 1
		{
			unsigned long long int number = m_WholeNumber;	//number is not changed by m_setFactorPair, but changed by prime factorization
			unsigned long long int factorTest = MIN_FACTOR; //number to be tested if it is a factor
			m_setFactorPair(number, factorTest);
		}
	}

	virtual void primeFactorise()
	{
		if (m_WholeNumber == MIN_WHOLE_NUM) // can't factorise 0
			std::cout << "Can't factorise 0!" << std::endl;
		else if (!m_primeFactors.empty())
			std::cout << "Already prime-factorized!" << std::endl;
		else if (m_WholeNumber == MIN_FACTOR)								  //number equals 1
			std::cout << "Number 1 has no prime decomposition." << std::endl; // vector remains empty
		else																  // do factorization for number greater then 1
		{
			unsigned long long int number = m_WholeNumber; //number is not changed by m_setFactorPair, but changed by prime factorization
			unsigned long long int factorTest = 1;		   //number to be tested if it is a factor
			unsigned long long int factorCounter = 1;
			m_setPrimeFactor(number, ++factorTest, factorCounter); //start prime factorization with 2
		}
	}

	//TODO
	const std::vector<unsigned long long int> getLeastCommonPrimeFactors(const WholeNumber &other)
	{
	}

	//TODO rework
	const std::vector<unsigned long long int> getCommonPrimeFactors(const WholeNumber &other) const
	{
		//m_primeFactors and other m_primefactors should be primefactorised
		std::vector<unsigned long long int> commonPrimeFactors;
		if (m_WholeNumber == MIN_WHOLE_NUM || other.getWholeNumber() == MIN_WHOLE_NUM)
		{
			std::cout << "Please provide a number greater then 0." << std::endl;
			return commonPrimeFactors; //returning empty vector
		}

		if (m_WholeNumber == MIN_FACTOR || other.getWholeNumber() == MIN_FACTOR)
			return commonPrimeFactors; //no common prime-factor returning empty vector

		const std::vector<unsigned long long int> otherPrimeFactors = other.getPrimeFactors();
		for (unsigned int i = 0; i < m_primeFactors.size(); i++)
		{
			for (unsigned int j = 0; j < otherPrimeFactors.size(); j++)
			{
				if (m_primeFactors[i] == otherPrimeFactors[j])
				{
					commonPrimeFactors.push_back(m_primeFactors[i]);
					break;
				}
				if (m_primeFactors[i] < otherPrimeFactors[j])
					break;
				if (m_primeFactors[i] > otherPrimeFactors[j])
					continue;
			}
		}
		return commonPrimeFactors; //if no common prime factor was found, vector is empty
	}

	//TODO rework
	const unsigned long long int getGreatestCommonFactor(const WholeNumber &other) const
	{
		if (m_WholeNumber == MIN_WHOLE_NUM)
			return other.getWholeNumber();
		if (other.getWholeNumber() == MIN_WHOLE_NUM)
			return m_WholeNumber;

		unsigned long long int commonFactor = MIN_FACTOR;
		if (m_WholeNumber == MIN_FACTOR || other.getWholeNumber() == MIN_FACTOR)
			return commonFactor;

		const std::vector<unsigned long long int> otherPrimeFactors = other.getPrimeFactors();
		for (unsigned int i = 0; i < m_primeFactors.size(); i++)
		{
			for (unsigned int j = 0; j < otherPrimeFactors.size(); j++)
			{
				if (m_primeFactors[i] == otherPrimeFactors[j])
				{
					commonFactor *= m_primeFactors[i];
					break;
				}
				if (m_primeFactors[i] < otherPrimeFactors[j])
					break;
				if (m_primeFactors[i] > otherPrimeFactors[j])
					continue;
			}
		}
		return commonFactor;
	}

	//Greates Common Factor Method
	const unsigned long long int getLeastCommonMultiple(const WholeNumber &other) const
	{
		return (m_WholeNumber * other.getWholeNumber()) / getGreatestCommonFactor(other);
	}

	//TODO Prime Factorization Method

	//Regrouping whole numbers
	void regroupAs()
	{
		//TODO
	}

protected:
	void m_clear() // clear maps and vector members
	{
		if (!m_decomposeValues.empty())
			m_decomposeValues.clear();

		if (!m_expandValues.empty())
			m_expandValues.clear();

		if (!m_factorPairs.empty())
			m_factorPairs.clear();

		if (!m_primeFactors.empty())
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

	void m_setPrimeFactor(unsigned long long int &number, unsigned long long int &factorTest, unsigned long long int &factorCounter)
	{
		while (factorCounter != m_WholeNumber) //check if found all prime factors
		{
			while (number % factorTest == 0) //prime factorization starts with 2
			{
				m_primeFactors.push_back(factorTest);
				number /= factorTest;
				factorCounter *= factorTest; // all prime factors multiply equals number to be factorise
			}
			factorTest++;
		}
	}

	void m_setFactorPair(const unsigned long long int &number, unsigned long long int &factorTest)
	{
		while (m_factorPairs.count(number / factorTest) == 0) //check if already found factor
		{
			if (number % factorTest == 0) //found factor
			{
				m_factorPairs[factorTest] = (number / factorTest);
			}
			factorTest++; // next factor
		}
	}
};

class Integer : public WholeNumber
{
protected:
	long long int m_Integer;

public:
	Integer()
		: m_Integer(MIN_WHOLE_NUM) {}

	Integer(long long int number)
	{
		set(number);
	}

	virtual void set(long long int number)
	{
		if (number > MAX_INT)
			m_Integer = MAX_INT;
		else if (number < MIN_INT)
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

class RationalNumber : public Integer
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

	void primeFactorise()
	{
		m_Numerator.primeFactorise();
		m_Denominator.primeFactorise();
	}

	const RationalNumber getEquivalent(const RationalNumber &other)
	{
		//TODO
		return other;
	}

	bool isEquivalent(const RationalNumber &other)
	{
		//TODO
		return false; //(this->m_Numerator * other.m_Denominator) == (this->m_Denominator * other.m_Numerator);
	}
};

//TODO
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

//TODO
class CoordinatePlane
{
private:
	unsigned int size_y;
	unsigned int size_x;
	Segment m_y;
	Segment m_x;
	const Point2d m_origin(0, 0);

public:
};

//TODO
template <typename Data>
class FrequencyTable
{
private:
	std::vector<Data> m_values;
	std::map<Data, int> m_frequencyMap;

public:
};
