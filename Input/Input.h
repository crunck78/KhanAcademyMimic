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
	bool _checkExceptions; // true to compare input against values given
	T _input;
	const char* _badInputMessage;
	
public:
	Input(const char* badInputMessage = nullptr);
	Input(const std::vector<T> &values, const bool checkTrue = true, const char* badInputMessage = nullptr);
	Input(const T lowest, const T highest, const char* badInputMessage = nullptr);
	
	T getInput(const char* messageToUser = nullptr, const char* exceptionInputMessage = nullptr);
	std::vector<T> getInputs(const T &exit, const char* messageToUser = nullptr);
	std::vector<T> getInputs(const unsigned int stop, const char* messageToUser = nullptr);

	void setValues(const std::vector<T> values, const bool checkTrue = true, const char* badInputMessage = nullptr);
	void setRange(const T lowest, const T highest, const char* badInputMessage = nullptr);

private:
	void _setInput();
	bool _badValues();
	bool _badRange();
	bool _badExceptions();
	void _displayValues();
};

template <typename T> Input<T>::Input(const char* badInputMessage)
	:_checkValues(false), _checkRange(false), _checkExceptions(false), _badInputMessage(badInputMessage)
{}

template <typename T> Input<T>::Input(const std::vector<T> &values, const bool checkTrue, const char* badInputMessage)
	:_values(values), _checkValues(checkTrue), _checkRange(false), _checkExceptions(!checkTrue), _badInputMessage(badInputMessage)
{}

template <typename T> Input<T>::Input(const T lowest, const T highest, const char* badInputMessage)
	: _checkValues(false), _checkRange(true), _checkExceptions(false), _badInputMessage(badInputMessage)
{
	_values.push_back(lowest);
	_values.push_back(highest);
}

template <typename T> void Input<T>::setValues(const std::vector<T> values, const bool checkTrue, const char* badInputMessage)
{
	_values.clear();
	_values = values;
	_checkValues = checkTrue;
	_checkExceptions = !checkTrue;
	_badInputMessage = badInputMessage;
}

template <typename T> void Input<T>::setRange(const T lowest, const T highest, const char *badInputMessage)
{
	_values.clear();
	_values.push_back(lowest);
	_values.push_back(highest);
	_checkRange = true;
	_checkValues = false;
	_checkExceptions = false;
	_badInputMessage = badInputMessage;
}

template <typename T> void Input<T>::_setInput()
{
	std::cin >> _input;
	while (std::cin.fail()) 
	{
		if (_badInputMessage != nullptr)
			std::cerr << _badInputMessage;
		else
			std::cerr << "\nYour input could not be extracted!\nPlease try againe: ";

		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> _input;
	}
}

template <typename T> T Input<T>::getInput(const char* messageToUser, const char* exceptionInputMessage)
{
	if (messageToUser != nullptr)
		std::cout << messageToUser;
	_setInput();
	if (_checkValues)
	{
		while (_badValues())
		{
			std::cout << "Your input " << _input << " is not valid.\nPlease chose only one from the following values:\n";
			_displayValues();
			_setInput();
		}
	}

	if (_checkExceptions)
	{
		while (_badExceptions())
		{
			if (exceptionInputMessage != nullptr)
				std::cout << exceptionInputMessage << std::endl;
			else
			{
				std::cout << "Your input " << _input << " is not valid.\nPlease chose non of the following values:\n";
				_displayValues();
			}
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

template <typename T> std::vector<T> Input<T>::getInputs(const T &exit, const char* messageToUser)
{
	std::vector<T> inputs;
	T input = getInput(messageToUser);
	while (input != exit)
	{
		inputs.push_back(input);
		input = getInput(messageToUser);
	}
	return inputs;
}

//TODO implement a methode to get a n numbers of inputs
template <typename T> std::vector<T> Input<T>::getInputs(const unsigned int stop, const char* messageToUser)
{
	std::vector<T> inputs;
	for(unsigned int i = 0; i < stop; i++)
	{
		inputs.push_back(getInput(messageToUser));
	}
	return inputs;
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

template <typename T> bool Input<T>::_badExceptions()
{
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		if (_input == _values[i])
		{
			std::cerr << "Input " << _input << " matches one of the exception values!" << std::endl;
			return true;//match found, return bad input
		}
	}
	return false;//no match found, return no bad input
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
		std::cout << "[ "<< _values[i] << " ]  ";
	}
	std::cout << std::endl;
}
#endif
