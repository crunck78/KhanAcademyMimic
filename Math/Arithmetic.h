#pragma once

float sumOf(float a, float b)
{
	return (a + b);
}

float diffOf(float a, float b)
{
	return (a - b);
}

float multOf(float a, float b)
{
	return (a * b);
}

float divOf(float a, float b)
{
	//TODO: Guard against 0 division
	return (a / b);
}

float power(float base, int expon)
{
	if (expon == 1)
		return expon;
	int temp = base;
	for (int i = 1; i < expon; i++)
	{
		temp = multOf(temp, base);
	}
	return temp;
}

bool isPossitive(float a)
{
	return (a > 0.0f);
}

bool isNegative(float a)
{
	return (a < 0.0f);
}

bool isOpposite(float a, float b)
{
	return sumOf(a, b) == 0.0f;
}

float opposite(float a)
{
	return diffOf(a, multOf(2.0f, a));
}

float absoluteValue(float a)
{
	if (isNegative(a))
		return opposite(a);

	return a;
}