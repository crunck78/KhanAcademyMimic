#pragma once
#include <iostream>

//ASCII CODE FOR MATHEMATICAL OPERATIONS
enum BinaryOperations
{
	EQUAL = 61, ADDITION = 43, SUBSTRACTION = 45, MULTIPLICATION = 42, DIVISION = 47, LCM = 109
};

//TODO: Implement Unary Operations
enum UnaryOperations
{
	ABSOLUTE = 97, OPPOSITE = 111
};

enum Converstions
{
	MIXEDNUM_TO_IMPRFRACT = 1, IMPRFRACT_TO_MIXEDNUM = -1, 
};

//TODO
static const std::vector<char> validOperations = { EQUAL, ADDITION, SUBSTRACTION, MULTIPLICATION, DIVISION };

template<typename Number>
bool isPossitive(const Number &a)
{
	return (a > 0);
}

template<typename Number>
bool isNegative(const Number &a)
{
	return (a < 0);
}

template<typename Number>
bool isOpposite(const Number &a, const Number &b)
{
	return a == -b;
}

template<typename Number>
bool isEven(const Number &a)
{
	return (a % 2) == 0;
}

template<typename Number>
bool isDivisible(const Number &a, const Number &b)
{
	return (a % b) == 0;
}

template<typename Number>
const Number midValue(const Number &a, const Number &b)
{
	return (a + b) / 2;
}


template<typename Number>
const Number getSum(const Number &a, const Number &b)
{
	return a + b;
}

template<typename Number>
const Number getSub(const Number &a, const Number &b)
{
	return a - b;
}

template<typename Number>
const Number getProd(const Number &a, const Number &b)
{
	return a * b;
}

template<typename Number>
const Number getDiv(const Number &a, const Number &b)
{
	if (b == 0)
		std::cerr << "ERROR::ARITHMETIC::LINE78::Division by 0 is undefinde!" << std::endl;
	return a / b;
}

template<typename Number>
const unsigned int getRemainder(const Number &a, const Number &b)
{
	return a % b;
}


const unsigned int getLeastCommonMultiple(const unsigned int a, const unsigned int b)
{
	unsigned int aMultiple = a;
	unsigned int bMultiple = b;
	while (aMultiple != bMultiple)
	{
		if (aMultiple < bMultiple)
			aMultiple += a;
		else
			bMultiple += b;
	}
	return aMultiple;
}

template<typename Number>
const Number getResult(const Number &a, const Number &b, const char operation)
{
	Number result = 0;
	switch ((int)operation)
	{
	case ADDITION: result = getSum(a, b); break;
	case SUBSTRACTION: result = getSub(a, b); break;
	case MULTIPLICATION: result = getProd(a, b); break;
	case DIVISION: result = getDiv(a, b); break;
	default: std::cerr << "UNKNOWN OPERATION OF SIGN: " << operation << std::endl;
		std::cerr << "RETURN 0" << std::endl;
		break;
	}
	return result;
}

template<typename Number>
const Number getOpposite(const Number &a)
{
	return 0 - a;
}

template<typename Number>
const Number getAbsoluteValue(const Number &a)
{
	if (isNegative(a))
		return getOpposite(a);
	return a;
}

template<typename Number>
const Number getResult(const Number &a, const char operation)
{
	Number result = 0;
	switch ((int)operation)
	{
	case OPPOSITE: result = getOpposite(a); break;
	case ABSOLUTE: result = getAbsoluteValue(a); break;
	default: std::cerr << "UNKNOWN OPERATION OF SIGN: " << operation << std::endl;
		std::cerr << "RETURN 0" << std::endl;
		break;
	}
	return result;
}

/*class WholeNumber
{
private:
	unsigned int m_wholeNumber;
	
public:
	WholeNumber()
		:m_wholeNumber(0) {}
	WholeNumber(const int n)
		:m_wholeNumber(n) {}
	WholeNumber(const WholeNumber &other)
		:m_wholeNumber(other.m_wholeNumber) {}

	WholeNumber& operator=(const WholeNumber &rhs)
	{
		if (this != &rhs)
		{
			this->m_wholeNumber = rhs.m_wholeNumber;
		}
		return *this;
	}

	WholeNumber& operator+=(const WholeNumber &rhs)
	{
		this->m_wholeNumber = this->m_wholeNumber + rhs.m_wholeNumber;
		return *this;
	}

	friend WholeNumber operator+(WholeNumber lhs, const WholeNumber &rhs)
	{
		lhs += rhs;
		return lhs;
	}

	WholeNumber& operator-=(const WholeNumber &rhs)
	{
		if (this->m_wholeNumber < rhs.m_wholeNumber)
			std::cerr << "Can not substract a bigger Whole number from a smaller Whole number!" << std::endl;
		else
			this->m_wholeNumber = this->m_wholeNumber - rhs.m_wholeNumber;
		return *this;
	}

	friend WholeNumber operator-(WholeNumber lhs, const WholeNumber &rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	WholeNumber& operator-()
	{
		std::cerr << "Whole numbers have no opposites!" << std::endl;
		return *this;
	}

	WholeNumber& operator++()
	{
		this->m_wholeNumber++;
		return *this;
	}

	WholeNumber& operator++(int)
	{
		this->m_wholeNumber++;
		return *this;
	}

	WholeNumber& operator--()
	{
		if (this->m_wholeNumber == 0)
			std::cerr << "Whole numbers can not be smaller then 0!" << std::endl;
		else
			this->m_wholeNumber--;
		return *this;
	}

	WholeNumber& operator--(int)
	{
		if (this->m_wholeNumber == 0)
			std::cerr << "Whole numbers can not be smaller then 0!" << std::endl;
		else
			this->m_wholeNumber--;
		return *this;
	}

	WholeNumber& operator*=(const WholeNumber &rhs)
	{
		this->m_wholeNumber = this->m_wholeNumber * rhs.m_wholeNumber;
		return *this;
	}

	friend WholeNumber operator*(WholeNumber lhs, const WholeNumber &rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	WholeNumber& operator/=(const WholeNumber &rhs)
	{
		this->m_wholeNumber = this->m_wholeNumber / rhs.m_wholeNumber;
		return *this;
	}

	friend WholeNumber operator/(WholeNumber lhs, const WholeNumber &rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend bool operator==(const WholeNumber &lhs, const WholeNumber &rhs)
	{
		return lhs.m_wholeNumber == rhs.m_wholeNumber;
	}

	friend bool operator!=(const WholeNumber &lhs, const WholeNumber &rhs) { return !operator==(lhs, rhs); }

	friend bool operator< (const WholeNumber &lhs, const WholeNumber &rhs)
	{
		return lhs.m_wholeNumber < rhs.m_wholeNumber;
	}

	friend bool operator> (const WholeNumber &lhs, const WholeNumber &rhs) { return operator< (rhs, lhs); }
	friend bool operator<=(const WholeNumber &lhs, const WholeNumber &rhs) { return !operator> (lhs, rhs); }
	friend bool operator>=(const WholeNumber &lhs, const WholeNumber &rhs) { return !operator< (lhs, rhs); }


	friend std::ostream& operator<<(std::ostream& os, const WholeNumber &obj)
	{
		os << obj.m_wholeNumber;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, WholeNumber &obj)
	{
		std::cout << "Enter Whole number(Only Positive Integer Accepted): ";
		is >> obj.m_wholeNumber;
		return is;
	}
};*/

class Fraction
{
private:
	int m_numerator;
	int m_denominator;//if 0, is undefinde, if < 0 assigned the numerator and make denominator possitive

public:
	Fraction()
		:m_numerator(0), m_denominator(1) {}
	Fraction(const int n)
		:m_numerator(n), m_denominator(1) {}

	Fraction(const int n, const int d)
	{
		set(n, d);
	}

	Fraction(const Fraction &other)
	{
		set(other.m_numerator, other.m_denominator);
	}

	Fraction& operator=(const Fraction &rhs)
	{
		if (this != &rhs)
		{
			this->set(rhs.m_numerator, rhs.m_denominator);
		}
		return *this;
	}

	Fraction& operator+=(const Fraction &rhs)
	{
		if (this->m_denominator != rhs.m_denominator)
		{
			Fraction commonDenominator = rhs;
			toCommonDenominators(*this, commonDenominator);
			this->m_numerator = this->m_numerator + commonDenominator.m_numerator;
		}
		else
			this->m_numerator = this->m_numerator + rhs.m_numerator;
		return *this;
	}

	friend Fraction operator+(Fraction lhs, const Fraction &rhs)
	{
		lhs += rhs;
		return lhs;
	}

	Fraction& operator-=(const Fraction &rhs)
	{
		if (this->m_denominator != rhs.m_denominator)
		{
			Fraction commonDenominator = rhs;
			toCommonDenominators(*this, commonDenominator);
			this->m_numerator = this->m_numerator - commonDenominator.m_numerator;
		}
		else
			this->m_numerator = this->m_numerator - rhs.m_numerator;
		return *this;
	}

	friend Fraction operator-(Fraction lhs, const Fraction &rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	Fraction operator-()
	{
		return Fraction(-this->m_numerator);
	}

	Fraction& operator++()
	{
		this->m_numerator++;
		return *this;
	}

	Fraction& operator++(int)
	{
		this->m_numerator++;
		return *this;
	}

	Fraction& operator--()
	{
		this->m_numerator--;
		return *this;
	}

	Fraction& operator--(int)
	{
		this->m_numerator--;
		return *this;
	}

	Fraction& operator*=(const Fraction &rhs)
	{
		this->m_numerator = this->m_numerator * rhs.m_numerator;
		this->m_denominator = this->m_denominator * rhs.m_denominator;
		return *this;
	}

	friend Fraction operator*(Fraction lhs, const Fraction &rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	Fraction& operator/=(const Fraction &rhs)
	{
		this->m_numerator = this->m_numerator * rhs.m_denominator;
		this->m_denominator = this->m_denominator * rhs.m_numerator;
		return *this;
	}

	friend Fraction operator/(Fraction lhs, const Fraction &rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend bool operator==(const Fraction &lhs, const Fraction &rhs)
	{
		return (lhs.m_numerator * rhs.m_denominator) == (lhs.m_denominator * rhs.m_numerator);
	}

	friend bool operator!=(const Fraction &lhs, const Fraction &rhs) { return !operator==(lhs, rhs); }

	friend bool operator< (const Fraction &lhs, const Fraction &rhs)
	{
		if (lhs.m_denominator != rhs.m_denominator)
			return (lhs.m_numerator * rhs.m_denominator) < (rhs.m_numerator * lhs.m_denominator);
		else
			return lhs.m_numerator < rhs.m_numerator;
	}

	friend bool operator> (const Fraction &lhs, const Fraction &rhs) { return operator< (rhs, lhs); }
	friend bool operator<=(const Fraction &lhs, const Fraction &rhs) { return !operator> (lhs, rhs); }
	friend bool operator>=(const Fraction &lhs, const Fraction &rhs) { return !operator< (lhs, rhs); }


	friend std::ostream& operator<<(std::ostream& os, const Fraction &obj)
	{
		os << obj.m_numerator << '/' << obj.m_denominator;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Fraction &obj)
	{
		std::cout << "Enter numerator: ";
		is >> obj.m_numerator;
		std::cout << "Enter denominator: ";
		is >> obj.m_denominator;
		while (obj.m_denominator == 0)
		{
			std::cout << "Fraction is undefinde if denominator equals to 0!" << std::endl;
			std::cout << "Enter denominator: ";
			is >> obj.m_denominator;
		}
		return is;
	}
	
	void set(const int n, const int d)
	{
		if (d < 0)
		{
			m_numerator = -n;
			m_denominator = -d;
		}
		else
		{
			m_numerator = n;
			m_denominator = d;
		}
	}

	const int getNumerator() const
	{
		return m_numerator;
	}

	const int getDenominator() const
	{
		return m_denominator;
	}

	friend void toCommonDenominators(Fraction &lhs, Fraction &rhs)
	{
		//find smallest common multiple of the fractions denominators
		const unsigned int commonDenominator = getLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);

		//first set the numerators(we need the ooriginal denominator unchanged to set the correct numerator)
		lhs.m_numerator *= commonDenominator / lhs.m_denominator;
		rhs.m_numerator *= commonDenominator / rhs.m_denominator;

		//second set the denominators
		lhs.m_denominator = commonDenominator;
		rhs.m_denominator = commonDenominator;
	}

	const int getResult() const
	{
		return (m_numerator / m_denominator);
	}

	const unsigned int getRemainder() const
	{
		return (m_numerator % m_denominator);
	}

	//TODO
	const Fraction getSimplification()
	{
		Fraction simplification;
		int smallestDivisor;
		int biggerDivisor;
		if (isImproper())
		{
			smallestDivisor = m_denominator;
			biggerDivisor = getAbsoluteValue(m_numerator);
		}
		else
		{
			smallestDivisor = getAbsoluteValue(m_numerator);
			biggerDivisor = m_denominator;
		}

		if (isDivisible(biggerDivisor, smallestDivisor))
		{
			simplification.set(m_numerator / smallestDivisor, m_denominator / smallestDivisor);
		}

		return simplification;
	}

	//TODO
	void simplify()
	{
		int smallestDivisor;
		int biggerDivisor;
		if (isImproper())
		{
			smallestDivisor = m_denominator;
			biggerDivisor = getAbsoluteValue(m_numerator);
		}
		else
		{
			smallestDivisor = getAbsoluteValue(m_numerator);
			biggerDivisor = m_denominator;
		}

		if (isDivisible(biggerDivisor, smallestDivisor))
		{
			m_numerator /= smallestDivisor;
			m_denominator /= smallestDivisor;
		}
		else
		{
			int factorTest = 2;//smallest prime Number
			while (factorTest < smallestDivisor)
			{
				if (isDivisible(biggerDivisor, factorTest) && isDivisible(smallestDivisor, factorTest))
				{
					m_numerator /= factorTest;
					m_denominator /= factorTest;
					smallestDivisor /= factorTest;
				}
				else
					factorTest++;
			}
		}
	}

	bool isUndefined()
	{
		return m_denominator == 0;
	}

	bool isImproper()
	{
		return getAbsoluteValue(m_numerator) >= m_denominator;
	}

	bool isUnit()
	{
		return (m_numerator == 1 || m_numerator == -1);
	}
};

class MixedNumber : public Fraction
{
private:
	int m_wholePart;
public:
	MixedNumber()
		:Fraction(), m_wholePart(0) {}

	MixedNumber(const Fraction &improperFraction)
		:Fraction(improperFraction.getRemainder(), improperFraction.getDenominator()), m_wholePart(improperFraction.getResult()) {}

	MixedNumber(const MixedNumber &other)
	{
		m_wholePart = other.m_wholePart;
		this->set(other.getNumerator(), other.getDenominator());
	}

	const Fraction getImproperFraction() const
	{
		Fraction improper;
		const int numerator = m_wholePart * this->getDenominator() + this->getNumerator();
		improper.set(numerator, this->getDenominator());
		return improper;
	}

	const MixedNumber getMixedNumberFrom(const Fraction &improper)
	{
		const MixedNumber converted(improper);
		return converted;
	}

	friend std::istream& operator>>(std::istream& is, MixedNumber &obj)
	{
		std::cout << "Enter Whole Part:";
		is >> obj.m_wholePart;
		int n, d;
		std::cout << "Enter numerator: ";
		is >> n;
		std::cout << "Enter denominator: ";
		is >> d;
		while (d == 0)
		{
			std::cout << "Fraction is undefinde if denominator equals to 0!" << std::endl;
			std::cout << "Enter denominator: ";
			is >> d;
		}
		obj.set(n, d);
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const MixedNumber &obj)
	{
		os << obj.m_wholePart << '(' << obj.getNumerator() << '/' << obj.getDenominator() << ')';
		return os;
	}
};