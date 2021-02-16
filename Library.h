#pragma once

struct Vector2
{
public:
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float x;
	float y;
};

struct Vector2Int
{
public:
	Vector2Int()
	{
		x = 0;
		y = 0;
	}
	Vector2Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
};

class Library
{
public:
	float static clamp(float value, float min, float max)
	{
		if (value >= min && value <= max)
			return value;

		if (value < min)
			return min;

		if (value > max)
			return max;
	}
};