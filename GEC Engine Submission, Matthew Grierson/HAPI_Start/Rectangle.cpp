#include "Rectangle.h"




Rectangle::Rectangle(int width, int height)
{
	right = width;
	bottom = height;
}


Rectangle::~Rectangle()
{
}

void Rectangle::Translate(int dx, int dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}

//function to clip one rectangle to another rectangle  so you only draw what is on screen or visible.
void Rectangle::ClipTo(const Rectangle &other)
{
	left = std::max(left, other.left);
	right = std::min(right, other.right);
	top = std::max(top, other.top);
	bottom = std::min(bottom, other.bottom);
}

bool Rectangle::CompletelyOutside(const Rectangle &other) const
{
	if (left > other.right || right < other.left || top > other.bottom || bottom < other.top)
	{
		return true;
	}
	return false;
}

bool Rectangle::CompletelyContains(const Rectangle &other) const
{
	if (left > other.left && right < other.right && top > other.top && bottom < other.bottom)
	{
		return true;
	}
	return false;
}

//void Rectangle::Resize(float percentage)
//{
//	int width = CalculateWidth();
//	int height = CalculateHeight();
//
//	percentage = (100 - percentage) / 100;
//	int newWidth = width * percentage;
//	int newHeight = height * percentage;
//	
//
//	int x = (width - newWidth) / 2;
//	int y = (height - newHeight) / 2;
//
//	Rectangle newRect(newWidth, newHeight);
//	newRect.Translate(x, y);
//
//	ClipTo(newRect);
//	
//}