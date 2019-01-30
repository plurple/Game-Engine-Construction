#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"


using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(const std::string &filename, bool alph = true, int framesX = 1, int framesY = 1); //default to 1 sprite and specify if there are more than one.
	~Sprite();
	void Blit(BYTE *screen, int screenWidth, int posX, int posY, Rectangle clippedRect, int frameNumber);
	Rectangle GetRect(); //creates rectangle to allow clipping and collision.
	BYTE* GetPnter() { return spritePnter; }
	int GetSpriteWidth() { return spriteWidth; }
	Rectangle GetFrameRect(Rectangle rect, int frameNumber);
	void SetWidth(int newWidth);
	

private:
	int spriteWidth, spriteHeight;
	BYTE *spritePnter{ nullptr };
	int frameWidth, frameHeight, numberOfFramesX, numberOfFramesY; //information to work with sprite sheets and animation.
	Rectangle frameRectangle{ 0, 0 };
	bool isAlpha{ true };
	
	
};

