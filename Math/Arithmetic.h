#pragma once

template<typename Number>
bool isPossitive(Number a)
{
	return (a > 0.0f);
}

template<typename Number>
bool isNegative(Number a)
{
	return (a < 0.0f);
}

template<typename Number>
bool isOpposite(Number a, Number b)
{
	return (a + b) == 0.0f;
}

template<typename Number>
Number opposite(Number a)
{
	return (0.0f - a);
}

bool isEven(long long int a)
{
	return (long double)(a % 2) == 0.0f;
}

bool isDivisible(long long int a, long long int b)
{
	return (float)(a % b) == 0.0f;
}

template<typename Number>
Number absoluteValue(Number a)
{
	if (isNegative(a))
		return opposite(a);
	return a;
}

template<typename Number>
long double midValue(Number a, Number b)
{
	return (long double)((a + b) / 2.0f);
}
