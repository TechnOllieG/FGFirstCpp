#pragma once
#include <cmath>

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

	float sqrMagnitude()
	{
		return x * x + y * y;
	}

	float magnitude()
	{
		return sqrt(sqrMagnitude());
	}

	void Normalize()
	{
		float length = magnitude();
		if (length > 0)
		{
			x /= length;
			y /= length;
		}
	}

	Vector2 normalized()
	{
		float length = magnitude();
		Vector2 vector = Vector2(x, y);
		if (length > 0)
		{
			vector.x /= length;
			vector.y /= length;
		}
		return vector;
	}

	static float Dot(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
};

static Vector2 operator+(Vector2 lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static void operator+=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

static Vector2 operator-(Vector2 lhs, const Vector2 rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

static Vector2 operator-(Vector2 current)
{
	return Vector2(-current.x, -current.y);
}

static void operator-=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
}

static Vector2 operator*(Vector2 lhs, const float rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

static void operator*=(Vector2 lhs, const float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
}

static Vector2 operator*(Vector2 lhs, const Vector2 rhs)
{
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

static void operator*=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
}

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
	Vector2Int(Vector2 vector)
	{
		this->x = (int) vector.x;
		this->y = (int) vector.y;
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

	float static InverseLerp(float a, float b, float value)
	{
		return (value - a) / (b - a);
	}
};