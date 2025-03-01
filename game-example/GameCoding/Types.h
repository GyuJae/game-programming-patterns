#pragma once
#include <cmath>
#include <windows.h>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x(static_cast<float>(pt.x)), y(static_cast<float>(pt.y)) {}

	Vector operator+(const Vector& other) const
	{
		return Vector(x + other.x, y + other.y);
	}

	Vector operator-(const Vector& other) const
	{
		return Vector(x - other.x, y - other.y);
	}

	Vector operator*(float value) const
	{
		return Vector(x * value, y * value);
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	float LengthSquared() const
	{
		return x * x + y * y;
	}

	float Length() const
	{
		return std::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 1e-9f)
			return;
		x /= length;
		y /= length;
	}

	float Dot(const Vector& other) const
	{
		return x * other.x + y * other.y;
	}

	float Cross(const Vector& other) const
	{
		return x * other.y - y * other.x;
	}

	float x = 0;
	float y = 0;
};

struct VectorInt
{
	VectorInt() {}
	VectorInt(int32 x, int32 y) : x(x), y(y) {}
	VectorInt(POINT pt) : x(pt.x), y(pt.y) {}

	VectorInt operator+(const VectorInt& other) const
	{
		return VectorInt(x + other.x, y + other.y);
	}

	VectorInt operator-(const VectorInt& other) const
	{
		return VectorInt(x - other.x, y - other.y);
	}

	VectorInt operator*(int32 value) const
	{
		return VectorInt(x * value, y * value);
	}

	bool operator<(const VectorInt& other) const
	{
		return (x != other.x) ? (x < other.x) : (y < other.y);
	}

	bool operator>(const VectorInt& other) const
	{
		return (x != other.x) ? (x > other.x) : (y > other.y);
	}

	bool operator==(const VectorInt& other) const
	{
		return x == other.x && y == other.y;
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}

	int32 LengthSquared() const
	{
		return x * x + y * y;
	}

	float Length() const
	{
		return std::sqrt(static_cast<float>(LengthSquared()));
	}

	int32 Dot(const VectorInt& other) const
	{
		return x * other.x + y * other.y;
	}

	int32 Cross(const VectorInt& other) const
	{
		return x * other.y - y * other.x;
	}

	operator Vector() const // Vector로 변환하는 연산자 추가
	{
		return Vector(static_cast<float>(x), static_cast<float>(y));
	}

	int32 x = 0;
	int32 y = 0;
};

using Pos = Vector;
using Vec2 = Vector;
using Vec2Int = VectorInt;
