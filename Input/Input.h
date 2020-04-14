#ifndef INPUT_H
#define INPUT_H

#define LOWEST  0
#define HIGHEST 1

#include <iostream>
#include <vector>

template<typename T> class Input
{
private:
	std::vector<T> _values; // values to commpare input with
	bool _checkValues; // true to commpare input with values given
	bool _checkRange; // true to compare input within a given range
	//bool _checkException; // true to compare input against values given
	T _input;
	
public:
	Input();
	Input(const std::vector<T> &values);
	Input(const T lowest, const T highest);
	
	T getInput(const char* messageToUser = nullptr);

private:
	void _setInput();
	bool _badValues();
	bool _badRange();
	void _displayValues();
};

template <typename T> Input<T>::Input()
	:_checkValues(false), _checkRange(false)
{}

template <typename T> Input<T>::Input(const std::vector<T> &values)
	:_values(values), _checkValues(true), _checkRange(false)
{}

template <typename T> Input<T>::Input(const T lowest, const T highest)
	: _checkValues(false), _checkRange(true)
{
	_values.push_back(lowest);
	_values.push_back(highest);
}

template <typename T> void Input<T>::_setInput()
{
	std::cin >> _input;
	while (std::cin.fail()) 
	{
		std::cerr << "Your input could not be extracted!\nPlease try againe: ";
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> _input;
	}
}

template <typename T> T Input<T>::getInput(const char* messageToUser)
{
	if (messageToUser != nullptr)
		std::cout << messageToUser;
	_setInput();
	if (_checkValues)
	{
		while (_badValues())
		{
			std::cout << "Your input " << _input << " is not valid.\nPlease chose one of the following values:\n";
			_displayValues();
			_setInput();
		}
	}

	if (_checkRange)
	{
		while (_badRange())
		{
			std::cerr << "Your input " << _input << " is not valid.\nPlease chose a value in the range of the following values: ";
			_displayValues();
			_setInput();
		}
	}
	return _input;
}

template <typename T> bool Input<T>::_badValues()
{
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		if (_input == _values[i])
			return false;//match found, return no bad input
	}
	std::cerr << "Input " << _input << " matches non of the valid values!" << std::endl;
	return true;//no match found, return bad input
}

template <typename T> bool Input<T>::_badRange()
{
	if (_input < _values[LOWEST])
	{
		std::cerr << "Input " << _input << " to small!" << std::endl;
		return true;
	}
	else if (_input > _values[HIGHEST])
	{
		std::cerr << "Input " << _input << " to big!" << std::endl;
		return true;
	}
	else
		return false;
}

template <typename T> void Input<T>::_displayValues()
{
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		std::cout << _values[i] << ", ";
	}
	std::cout << std::endl;
}
#endif