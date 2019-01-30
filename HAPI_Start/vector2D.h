#pragma once
class vector2D
{
public:
	vector2D(float x = 0.0, float y = 0.0) : X(x), Y(y) {};	
	~vector2D();

	float DotProduct(const vector2D &other) const;
	float length() const;
	float lengthSquared() const;
	vector2D Dist(vector2D &other);
	vector2D normalize();

	vector2D operator + (float scalar);
	vector2D operator - (float scalar);
	vector2D operator * (float scalar);
	vector2D operator / (float scalar);
	vector2D operator + (const vector2D &other);
	vector2D operator - (const vector2D &other);
	vector2D operator += (const vector2D &other);
	vector2D operator -= (const vector2D &other);
	vector2D operator = (const vector2D &other);
	bool operator == (const vector2D &other);
	bool operator != (const vector2D &other);
	
	float X{ 0 };
	float Y{ 0 };
};

