#pragma once

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
	return (a + b) == 0.0f;
}

float opposite(float a)
{
	return (0 - a);
}

float absoluteValue(float a)
{
	if (isNegative(a))
		return opposite(a);

	return a;
}
