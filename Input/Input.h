#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>

template<typename T> class Input
{
private:
	bool _checkInput; // true for commpare input with values
	T _input;
	std::vector<T> _values; // values to commpare against input

public:
	Input(const std::vector<T> &values);
	Input();

	T getInput();

private:
	void _setInput();
	bool _badInput();
	void _displayValues();
};

template <typename T> Input<T>::Input()
	: _checkInput(false)
{}

template <typename T> Input<T>::Input(const std::vector<T> &values)
	: _values(values), _checkInput(true)
{}

template <typename T> void Input<T>::_setInput()
{
	std::cin >> _input;
	while (std::cin.fail()) 
	{
		std::cout << "Your input " << _input << " could not be extracted!/nPlease try againe: ";
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> _input;
	}
}

template <typename T> T Input<T>::getInput()
{
	_setInput();
	if (_checkInput)
	{
		while (_badInput())
		{
			std::cout << "Your input " << _input << " is not valid./nPlease chose one of the following values:/n";
			_displayValues();
			_setInput();
		}
	}
	return _input;
}

template <typename T> bool Input<T>::_badInput()
{
	for (int i = 0; i < _values.size(); i++)
	{
		if (_input == _values[i])
			return false;//match found, return no bad input
	}
	return true;//no match found, return bad input
}

template <typename T> void Input<T>::_displayValues()
{
	for (int i = 0; i < _values.size(); i++)
	{
		std::cout << _values[i] << ", ";
	}
	std::cout << std::endl;
}
#endif