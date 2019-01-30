#pragma once
#include <unordered_map>
#include <HAPI_lib.h>
#include "Rectangle.h"
#include "vector2D.h"

class Sprite;

using namespace HAPISPACE;

class Graphics
{

public:
	Graphics();
	~Graphics();
	void clearScreen(int col); // function to clear screen
	void changePixel(BYTE *pnter, HAPI_TColour colour); // function to change a pixels colour
	void CreateSprite(const std::string &fileName, const std::string &uniqueName, bool alpha, int numberOfFramesX = 1, int numberOfFramesY = 1); //creates sprite with a default number of frames as 1
	void RenderSprite(const std::string &uniqueName, vector2D screenPos, int frameNumber); // renders the sprite with no alpha and assumes 1 frame and so on frame 0.
	Rectangle GetSpriteRect(std::string name);
	Rectangle GetSpriteFrameRect(std::string name, Rectangle rect, int frmaeNumber);
	BYTE* GetSpritePnter(std::string name);
	int GetSpriteWidth(std::string name);
	void SetSpriteWidth(std::string name, int newWidth);
	
private:
	std::unordered_map<std::string, std::shared_ptr<Sprite>> spriteMap; //collection of sprites that have been loaded.
	int screenWidth{ 1000 };
	int screenHeight{ 850 };
	BYTE *screen = nullptr;
	Rectangle screenSpace{ screenWidth, screenHeight }; //creates the rectangle of the screen to check if sprites are within this to draw them or not.
	
};

