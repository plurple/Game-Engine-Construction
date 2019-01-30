#pragma once
#include <algorithm>

class Rectangle
{
public:
	int left{ 0 }, right, top{ 0 }, bottom;

	Rectangle(int width, int height);
	~Rectangle();
	int CalculateWidth() const { return right - left; }
	int CalculateHeight() const { return bottom - top; }
	void ClipTo(const Rectangle &other);
	bool CompletelyContains(const Rectangle &other) const; //checks if one rectangle is completely inTag another rectangle.
	bool CompletelyOutside(const Rectangle &other) const; //checks if one rectangle is completely outTag another rectangle.
	void Translate(int dx, int dy); //converts a rectangle into another rectangle space.
	//void Resize(float percentage);
};
