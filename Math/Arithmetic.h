#pragma once

template<typename Number>
Number getSumOf(Number a, Number b)
{
	return a + b;
}

template<typename Number>
bool isPossitive(const Number a)
{
	return (a > 0);
}

template<typename Number>
bool isNegative(const Number a)
{
	return (a < 0);
}

template<typename Number>
bool isOpposite(const Number a, const Number b)
{
	return (a + b) == 0;
}

template<typename Number>
bool isEven(const Number a)
{
	return (a % 2) == 0;
}

template<typename Number>
bool isDivisible(const Number a, const Number b)
{
	return (a % b) == 0;
}

template<typename Number>
const Number opposite(const Number a)
{
	return (0 - a);
}

template<typename Number>
const Number absoluteValue(Number a)
{
	if (isNegative(a))
		return opposite(a);
	return a;
}

template<typename Number>
const long double midValue(Number a, Number b)
{
	return (long double)(a + b) / 2.0;
}