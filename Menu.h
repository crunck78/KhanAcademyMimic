#pragma once
#include <stdlib.h>
#include <iostream>
#include "Input/Input.h"
#include "Math/Arithmetic.h"

#define APP_NAME "KHAN ACADEMY"
#define EXIT 0

class Menu
{
protected:
	const char* _name;
	std::vector<Menu*> _p_options;
public:

	Menu()
		: _name("") {}

	Menu(const char* name)
		: _name(name) {}

	const char* getName() const
	{
		return _name;
	}

	void setOptions(const std::vector<Menu*> &options)
	{
			_p_options = options;
	}

	virtual Menu* selectOption()
	{
		std::vector<int> possibleOptions(_p_options.size());
		for (unsigned int i = 0; i < _p_options.size(); i++)
		{
			possibleOptions[i] = i;
		}
		Input<int> choise(possibleOptions, "Please enter positive integers only:");
		int selection = choise.getInput("SELECT AN OPTION: ");
		system("cls"); // clears console 
		return _p_options[selection];
	}

	const void displayOptions() const
	{
		std::cout << _name << std::endl;
		for (unsigned int i = EXIT; i < _p_options.size(); i++)
		{
			std::cout << i << ". " << _p_options[i]->getName() << std::endl;
		}
	}
};

template<typename Number>
class UnaryOperation : public Menu
{
private:
	char m_operation;
	Number m_result;
public:
	UnaryOperation(const char *name, const char operation)
		:Menu(name), m_operation(operation), m_result(0) {}

	Menu* selectOption()
	{
		Input<Number> numbers("Please enter integers only\n");
		const Number num1 = numbers.getInput("Enter number: ");
		system("cls");
		std::cout << num1 << " " << m_operation << " = " << getResult(num1, m_operation) << std::endl;
		return _p_options[EXIT];//return parent menu
	}
};

template<typename Number>
class BinaryOperation : public Menu
{
private:
	char m_operation;
	Number m_result;
public:
	BinaryOperation(const char *name, const char operation)
		:Menu(name), m_operation(operation), m_result(0) {}

	Menu* selectOption()
	{
		//TODO
		Input<Number> numbers("Please enter integers only\n");
		const Number num1 = numbers.getInput("Enter number: ");
		if (m_operation == DIVISION)
		{
			const std::vector<Number> exceptions = { 0 };
			numbers.setValues(exceptions, false, "Please enter integers only\n");
		}
		const Number  num2 = numbers.getInput("Enter second number: ", "Division by 0 is undefinde!");//if operation equals '/' guard against 0
		system("cls");
		std::cout << num1 << " " << m_operation << " " << num2 << " = " << getResult(num1, num2, m_operation) << std::endl;
		return _p_options[EXIT];//return parent menu
	}
};

template<typename T, typename N>
class Converter : public Menu
{
private:
	T m_from;
	N m_to;
	int m_convCode;
public:
	Converter(const char* name, const int convCode)
		: Menu(name), m_convCode(convCode) {}
};

class RemainderDivision : public Menu
{
private:
	unsigned int m_remainder;
public:
	RemainderDivision(const char* name)
		:Menu(name) {}

	Menu* selectOption()
	{
		Input<int> numbers("Please enter integers only : ");
		int num1 = numbers.getInput("Enter number: ");
		const std::vector<int> exceptions = { 0 };
		numbers.setValues(exceptions, false, "Please enter integers only\n");
		int num2 = numbers.getInput("Enter second number: ", "Division by 0 is undefined!");
		system("cls");
		std::cout << num1 << " / " << num2 << " = " << getDiv(num1, num2) << " R " << getRemainder(num1, num2) << std::endl;
		return _p_options[EXIT];//return parent menu
	}
};

class CommonDenominators : public Menu
{
public:
	CommonDenominators(const char* name)
		:Menu(name) {}
	Menu* selectOption()
	{
		Input<Fraction> numbers("Please enter integers only : ");
		Fraction num1 = numbers.getInput("Enter number: ");
		Fraction num2 = numbers.getInput("Enter second number: ");
		system("cls");
		std::cout << num1 << " , " << num2 << " <=> ";
		toCommonDenominators(num1, num2);
		std::cout << num1 << " , " << num2 << std::endl;
		return _p_options[EXIT];//return parent menu
	}
};

//Main Menu
Menu K_exit("EXIT");
Menu K_main(APP_NAME);

//Options for Main Menu
Menu K_math("MATH");

//Options for Menu Math
Menu K_arithmetic("ARITHMETIC");
Menu K_basicgeometrie("BASIC GEOMETRIE");
Menu K_prealgebra("PRE ALGEBRA");

//Options for Menu Arithmetic
BinaryOperation<int> K_addition("ADDITION", ADDITION);
BinaryOperation<int> K_substraction("SUBSTRACTION", SUBSTRACTION);
BinaryOperation<int> K_multiplication("MULTIPLICATION", MULTIPLICATION);
BinaryOperation<int> K_division("DIVISION", DIVISION);
RemainderDivision K_remainderDivision("DIVISION WITH REMAINDER");
UnaryOperation<int> K_opposite("OPPOSITE", OPPOSITE);
UnaryOperation<int> K_absolute("ABSOLUTE VALUE", ABSOLUTE);
Menu K_fractions("FRACTIONS");

//Options for Menu Fractions
BinaryOperation<Fraction> K_fraction_addition("ADDITION", ADDITION);
BinaryOperation<Fraction> K_fraction_substraction("SUBSTRACTION", SUBSTRACTION);
BinaryOperation<Fraction> K_fraction_multiplication("MULTIPLICATION", MULTIPLICATION);
BinaryOperation<Fraction> K_fraction_division("DIVISION", DIVISION);
UnaryOperation<Fraction> K_fraction_opposite("OPPOSITE", OPPOSITE);
UnaryOperation<Fraction> K_fraction_absolute("ABSOLUTE VALUE", ABSOLUTE);
CommonDenominators K_fraction_common_denominators("COMMON DENOMINATORS");

void initMenuTree()
{
	//Array of Options (Menu References) For Every Menu In The Order Of Declaration
	const std::vector<Menu*> K_mainOptions = { &K_exit, &K_math };

	const std::vector<Menu*> K_mathOptions = { &K_main, &K_arithmetic, &K_basicgeometrie, &K_prealgebra };

	const std::vector<Menu*> K_arithmeticOptions = { &K_math, &K_addition, &K_substraction, &K_multiplication, &K_division, &K_remainderDivision, &K_opposite, &K_absolute, &K_fractions };
	const std::vector<Menu*> K_basicgeometrieOptions = { &K_math };
	const std::vector<Menu*> K_prealgebraOptions = { &K_math };

	const std::vector<Menu*> K_additionOptions = { &K_arithmetic };
	const std::vector<Menu*> K_substractionOptions = { &K_arithmetic };
	const std::vector<Menu*> K_multiplicationOptions = { &K_arithmetic };
	const std::vector<Menu*> K_divisionOptions = { &K_arithmetic };
	const std::vector<Menu*> K_remainderDivisionOptions = { &K_arithmetic };
	const std::vector<Menu*> K_oppositeOptions = { &K_arithmetic };
	const std::vector<Menu*> K_absoluteOptions = { &K_arithmetic };
	const std::vector<Menu*> K_fractionsOptions = { &K_arithmetic,  &K_fraction_addition, &K_fraction_substraction, &K_fraction_multiplication, &K_fraction_division, &K_fraction_opposite, &K_fraction_absolute, &K_fraction_common_denominators};

	const std::vector<Menu*> K_fraction_additionOptions = { &K_fractions };
	const std::vector<Menu*> K_fraction_substractionOptions = { &K_fractions };
	const std::vector<Menu*> K_fraction_multiplicationOptions = { &K_fractions };
	const std::vector<Menu*> K_fractiom_divisionOptions = { &K_fractions };
	const std::vector<Menu*> K_fraction_oppositeOptions = { &K_fractions };
	const std::vector<Menu*> K_fraction_absoluteOptions = { &K_fractions };
	const std::vector<Menu*> K_fraction_commonDenominatorsOpptions = { &K_fractions };

	K_main.setOptions(K_mainOptions);

	K_math.setOptions(K_mathOptions);

	K_arithmetic.setOptions(K_arithmeticOptions);
	K_basicgeometrie.setOptions(K_basicgeometrieOptions);
	K_prealgebra.setOptions(K_prealgebraOptions);

	K_addition.setOptions(K_additionOptions);
	K_substraction.setOptions(K_substractionOptions);
	K_multiplication.setOptions(K_multiplicationOptions);
	K_division.setOptions(K_divisionOptions);
	K_remainderDivision.setOptions(K_remainderDivisionOptions);
	K_opposite.setOptions(K_oppositeOptions);
	K_absolute.setOptions(K_absoluteOptions);
	K_fractions.setOptions(K_fractionsOptions);
	
	K_fraction_addition.setOptions(K_fraction_additionOptions);
	K_fraction_substraction.setOptions(K_fraction_substractionOptions);
	K_fraction_multiplication.setOptions(K_fraction_multiplicationOptions);
	K_fraction_division.setOptions(K_fractiom_divisionOptions);
	K_fraction_opposite.setOptions(K_fraction_oppositeOptions);
	K_fraction_absolute.setOptions(K_fraction_absoluteOptions);
	K_fraction_common_denominators.setOptions(K_fraction_commonDenominatorsOpptions);
}