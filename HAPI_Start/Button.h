#pragma once
#include "vector2D.h"
#include "Rectangle.h"
#include <string>
#include "HAPI_lib.h"

using namespace HAPISPACE;

class Button
{
public:
	Button(std::string uniqueName, vector2D pos, Rectangle rectangle) : name(uniqueName), position(pos), rect(rectangle) {};
	~Button();

	std::string GetName() const { return name; }
	vector2D GetPosition() const { return position; }
	Rectangle GetRect() const { return rect; }
	HAPI_TColour GetCol() const { return colour; }

	void SetCol(HAPI_TColour col) { colour = col; }

private:
	std::string name;
	vector2D position;
	Rectangle rect;
	HAPI_TColour colour;
};

