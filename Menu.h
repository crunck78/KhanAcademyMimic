#pragma once
#include <iostream>
#include "Input\Input.h"

#define APP_NAME "KHAN ACADEMY"
#define EXIT 0

class Menu
{
protected:

	static unsigned int _nextIndex; // increases with every constructed object instance 
	static unsigned int _getNextIndex()
	{
		return _nextIndex++; 
	}

	const char* _name;
	unsigned int _index; // holds the nextIndex value as an object instance is constructed( default constructor does not count object instances 
	unsigned int _size; // size of array of menu pointers

	Menu **_p_options; // holds an array of menu pointer, holding refrences to a menu object
public:

	Menu()
		: _name(""), _index(0), _size(0), _p_options(nullptr)
	{

	}

	Menu(const char* name)
		: _name(name), _index(_getNextIndex()), _size(0), _p_options(nullptr)
	{

	}

	~Menu()
	{
		_deleteOptions();
	}

	static unsigned int getMenuTreeSize()
	{
		return _nextIndex;
	}

	const char* getName() const
	{
		return _name;
	}

	const unsigned int getIndex() const
	{
		return _index;
	}

	void setSize(const unsigned int size)
	{
		_size = size;
	}

	void setOptions(Menu *options[])
	{
		_p_options = new Menu*[_size];
		for (unsigned int i = 0; i < _size; i++)
		{
			_p_options[i] = options[i];
		}
	}

	const unsigned int getSize() const
	{
		return _size;
	}

	virtual Menu* selectOption()
	{
		std::vector<unsigned int> possibleOptions(_size);
		for (unsigned int i = 0; i < _size; i++)
		{
			possibleOptions[i] = i;
		}
		Input<unsigned int> choise(possibleOptions);
		unsigned int selection = choise.getInput("SELECT AN OPTION: ");
		return _p_options[selection];
	}

	const void displayOptions() const
	{
		std::cout << _name << std::endl;
		for (unsigned int i = EXIT; i < _size; i++)
		{
			std::cout << i << ". " << _p_options[i]->getName() << std::endl;
		}
	}
protected:
	void _deleteOptions()
	{
		if (_p_options != nullptr)
		{
			delete[] _p_options;
			_p_options = nullptr;
		}
	}
};

class Addition : public Menu
{
public:
	Addition(const char* name)
	{
		_index = _getNextIndex();
		_name = name;
		_size = 0;
		_p_options = nullptr;
	}

	Menu* selectOption()
	{
		//TODO
		return _p_options[EXIT];//return parent menu
	}
};

class Substraction : public Menu
{
public:
	Substraction(const char* name)
	{
		_index = _getNextIndex();
		_name = name;
		_size = 0;
		_p_options = nullptr;
	}

	Menu* selectOption()
	{
		//TODO
		return _p_options[EXIT];//return parent menu
	}
};

class Multiplication : public Menu
{
public:
	Multiplication(const char* name)
	{
		_index = _getNextIndex();
		_name = name;
		_size = 0;
		_p_options = nullptr;
	}

	Menu* selectOption()
	{
		//TODO
		return _p_options[EXIT];//return parent menu
	}
};

class Division : public Menu
{
public:
	Division(const char* name)
	{
		_index = _getNextIndex();
		_name = name;
		_size = 0;
		_p_options = nullptr;
	}

	Menu* selectOption()
	{
		//TODO
		return _p_options[EXIT];//return parent menu
	}
};

unsigned int Menu::_nextIndex = 0;

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
Addition K_addition("ADDITION");
Substraction K_substraction("SUBSTRACTION");
Multiplication K_multiplication("MULTIPLICATION");
Division K_division("DIVISION");

void initMenuTree()
{
	//Size of Menu ( Representing the Numbers Of Options Each Menu has ), in the Order Of Declaration
	const unsigned int K_mainSize = 2, K_mathSize = 4, K_arithmeticSize = 5, K_basicgeometrieSize = 1, K_prealgebraSize = 1, K_additionSize = 1, K_substractionSize = 1, K_multiplicationSize = 1, K_divisionSize = 1;

	K_addition.setSize(K_additionSize);
	K_substraction.setSize(K_substractionSize);
	K_multiplication.setSize(K_multiplicationSize);
	K_division.setSize(K_divisionSize);

	K_arithmetic.setSize(K_arithmeticSize);
	K_basicgeometrie.setSize(K_basicgeometrieSize);
	K_prealgebra.setSize(K_prealgebraSize);

	K_math.setSize(K_mathSize);

	K_main.setSize(K_mainSize);

	//Array of Options (Menu References) For Every Menu In The Order Of Declaration
	Menu *K_mainOptions[] = { &K_exit, &K_math };

	Menu *K_mathOptions[] = { &K_main, &K_arithmetic, &K_basicgeometrie, &K_prealgebra };

	Menu *K_arithmeticOptions[] = { &K_math, &K_addition, &K_substraction, &K_multiplication, &K_division };
	Menu *K_basicgeometrieOptions[] = { &K_math };
	Menu *K_prealgebraOptions[] = { &K_math };

	Menu *K_additionOptions[] = { &K_arithmetic };
	Menu *K_substractionOptions[] = { &K_arithmetic };
	Menu *K_multiplicationOptions[] = { &K_arithmetic };
	Menu *K_divisionOptions[] = { &K_arithmetic };

	K_main.setOptions(K_mainOptions);

	K_math.setOptions(K_mathOptions);

	K_arithmetic.setOptions(K_arithmeticOptions);
	K_basicgeometrie.setOptions(K_basicgeometrieOptions);
	K_prealgebra.setOptions(K_prealgebraOptions);

	K_addition.setOptions(K_additionOptions);
	K_substraction.setOptions(K_substractionOptions);
	K_multiplication.setOptions(K_multiplicationOptions);
	K_division.setOptions(K_divisionOptions);
}