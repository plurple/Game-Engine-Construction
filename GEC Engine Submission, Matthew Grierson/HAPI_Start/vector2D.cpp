#include "vector2D.h"
#include <math.h>
#include <iostream>




vector2D::~vector2D()
{
}

float vector2D::DotProduct(const vector2D &other) const
{
	float dot = X * other.X + Y * other.Y;
	return dot;
}

float vector2D::length() const
{
	float length = sqrtf(X * X + Y * Y);
	return length;
}

float vector2D::lengthSquared() const
{
	float lengthSquared = X * X + Y * Y;
	return lengthSquared;
}

vector2D vector2D::Dist(vector2D &other)
{
	vector2D temp;
	return temp = other - *this;
}

vector2D vector2D::normalize()
{
	if (lengthSquared() != 0)
	{
		float len = length();
		X /= len;
		Y /= len;
		return *this;
	}

	X = Y = 0.0;
	return *this;

}

vector2D vector2D::operator + (const vector2D &other)
{
	 return vector2D(X + other.X, Y + other.Y);
}

vector2D vector2D::operator - (const vector2D &other)
{
	return vector2D(X - other.X, Y - other.Y);
}

vector2D vector2D::operator + (float scalar)
{
	return vector2D(X + scalar, Y + scalar);
}

vector2D vector2D::operator - (float scalar)
{
	return vector2D(X - scalar, Y - scalar);
}

vector2D vector2D::operator * (float scalar)
{
	return vector2D(X * scalar, Y * scalar);
}

vector2D vector2D::operator / (float scalar)
{
	return vector2D(X / scalar, Y / scalar);
}

vector2D vector2D::operator += (const vector2D &other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

vector2D vector2D::operator -= (const vector2D &other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

vector2D vector2D::operator = (const vector2D &other)
{
	X = other.X;
	Y = other.Y;
	return *this;
}

bool vector2D::operator == (const vector2D &other)
{
	return (X == other.X && Y == other.Y);
}

bool vector2D::operator != (const vector2D &other)
{
	return (X != other.X || Y != other.Y);
}