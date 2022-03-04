#pragma once
#include <iostream>
#include "Math\Arithmetic.h"
#include <vector>
#include "Input\Input.h"
#define EXIT 0

template <typename Number>
class Calculator

{
private:
	std::vector<Number> m_numbers;
	char m_operation;

public:
	Calculator() {}

	Calculator(const char operation)
		: m_operation(operation) {}

	~Calculator() {}

	void clearNumbers()
	{
		m_numbers.clear();
	}

	void setNumbers(const std::vector<Number> &numbers)
	{
		m_numbers = numbers;
	}

	void setNumber(const Number &n)
	{
		m_numbers.push_back(n);
	}

	void setOperation(const char operation)
	{
		m_operation = operation;
	}

	void getOperationFromUser()
	{
		Input<char> operation(validOperations, "Please enter character type only");
		m_operation = operation.getInput("Enter operation sign: ");
	}

	void displayNumbers(const char operation = ' ', const char result = ' ')
	{
		unsigned int lastElementindex = m_numbers.size() - 1;
		for (unsigned int i = 0; i < m_numbers.size(); i++)
		{
			if (m_numbers[i] < 0) // output format to match a positive number
				std::cout << " [" << m_numbers[i] << "] ";
			else // output format to match a negative number
				std::cout << " [ " << m_numbers[i] << "] ";
			if (i != lastElementindex)
				std::cout << operation;
		}
		std::cout << result;
	}

	const std::vector<Number> getNumbers() const
	{
		return m_numbers;
	}

	Number getResult()
	{
		Number result;
		switch ((int)m_operation)
		{
		case ADDITION:
			result = getSumOf();
			break;
		case SUBSTRACTION:
			result = getDiffOf();
			break;
		case MULTIPLICATION:
			result = getProductOf();
			break;
		case DIVISION:
			result = getDivOf();
			break;
		default:
			std::cerr << "UNKNOWN OPERATION OF SIGN: " << m_operation << std::endl;
			std::cerr << "EMPTY INSTANCE OF ENTITY NUMBER RETURNED" << std::endl;
			break;
		}
		return result;
	}

	Number getSumOf()
	{
		Number sum = 0;
		if (!m_numbers.empty())
		{
			for (unsigned int i = 0; i < m_numbers.size(); i++)
			{
				sum += m_numbers[i];
			}
		}
		return sum;
	}

	Number getDiffOf()
	{
		Number diff = 0;
		if (!m_numbers.empty()) //guard against empty vector container
		{
			diff = m_numbers.front();	  // collecte first container element
			if (diff != m_numbers.back()) // guard against container of size 1
			{
				for (unsigned int i = 1; i < m_numbers.size(); i++) // start iterations from second container element
				{
					diff -= m_numbers[i];
				}
			}
		}
		return diff;
	}

	Number getProductOf()
	{
		Number product = 0;
		if (!m_numbers.empty()) //guard against empty vector container
		{
			product = m_numbers.front();	 // collecte first container element
			if (product != m_numbers.back()) // guard against container of size 1
			{
				for (unsigned int i = 1; i < m_numbers.size(); i++) // start iterations from second container element
				{
					product *= m_numbers[i];
				}
			}
		}
		return product;
	}

	Number getDivOf()
	{
		Number division = 0;
		if (!m_numbers.empty()) //guard against empty vector container
		{
			division = m_numbers.front();	  // collecte first container element
			if (division != m_numbers.back()) // guard against container of size 1
			{
				for (unsigned int i = 1; i < m_numbers.size(); i++) // start iterations from second container element
				{
					division /= m_numbers[i];
				}
			}
		}
		return division;
	}

	void convertToOpposites()
	{
		for (unsigned int i = 0; i < m_numbers.size(); i++)
		{
			m_numbers[i] = -m_numbers[i];
		}
	}

	void convertToAbsoluteValue()
	{
		for (unsigned int i = 0; i < m_numbers.size(); i++)
		{
			if (m_numbers[i] < 0)
			{
				m_numbers[i] = -m_numbers[i];
			}
		}
	}
};
