#include "Sprite.h"
#include "Rectangle.h"


Sprite::Sprite(const std::string &filename, bool alpha, int framesX, int framesY)
{
	if (!HAPI.LoadTexture(filename, &spritePnter, spriteWidth, spriteHeight))
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Texture not found", "Missing Texture", HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}
	frameWidth = spriteWidth / framesX;
	frameHeight = spriteHeight / framesY;
	numberOfFramesX = framesX;
	numberOfFramesY = framesY;
	Rectangle temp(frameWidth, frameHeight);
	frameRectangle = temp;
	isAlpha = alpha;
}


Sprite::~Sprite()
{
	delete[] spritePnter;
}

Rectangle Sprite::GetRect()
{
	return frameRectangle;
}

void Sprite::SetWidth(int newWidth)
{
	frameRectangle.right = newWidth;
}


void Sprite::Blit(BYTE *screen, int screenWidth, int screenX, int screenY, Rectangle clippedRect, int frameNumber)
{

	unsigned int screenOffset = (screenX + screenY * screenWidth) * 4;
	BYTE *screenPnter = screen + screenOffset;

	//an if statment to check still within the sprite sheet if not to wrap around. temporary fix.
	if (frameNumber >= (numberOfFramesX * numberOfFramesY))
	{
		frameNumber = frameNumber % (numberOfFramesX * numberOfFramesY);
	}
	clippedRect = GetFrameRect(clippedRect, frameNumber);
	int rectangleWidth = clippedRect.CalculateWidth();
	int rectangleHeight = clippedRect.CalculateHeight();
	unsigned int frameCorrection = ((clippedRect.left + clippedRect.top * spriteWidth) * 4);
	BYTE *texturePnter = spritePnter + frameCorrection;

	if (isAlpha)
	{
		BYTE blue;
		BYTE green;
		BYTE red;
		BYTE alpha;

		for (int i = 0; i < rectangleHeight; i++)
		{
			for (int j = 0; j < rectangleWidth; j++)
			{
				blue = texturePnter[0];
				green = texturePnter[1];
				red = texturePnter[2];
				alpha = texturePnter[3];

				if (alpha == 255)
				{
					memcpy(screenPnter, texturePnter, 4);
				}
				else if (alpha != 0)
				{
					screenPnter[0] = screenPnter[0] + ((alpha * (blue - screenPnter[0])) >> 8);
					screenPnter[1] = screenPnter[0] + ((alpha * (green - screenPnter[0])) >> 8);
					screenPnter[2] = screenPnter[0] + ((alpha * (red - screenPnter[0])) >> 8);
				}
				screenPnter += 4;
				texturePnter += 4;
			}

			screenPnter += (screenWidth - rectangleWidth) * 4;
			texturePnter += (spriteWidth - rectangleWidth) * 4;
		}
	}
	else
	{
		for (int i = 0; i < rectangleHeight; i++)
		{

			memcpy(screenPnter, texturePnter, rectangleWidth * 4);

			screenPnter += screenWidth * 4;
			texturePnter += spriteWidth * 4;
		}
	}
}


Rectangle Sprite::GetFrameRect(Rectangle rect, int frameNumber)
{
	int numberX = frameNumber % numberOfFramesX; //to work out the x frame offset.
	int numberY = frameNumber / numberOfFramesX; //to work out the y frame offset.
	rect.Translate((numberX * frameWidth), (numberY * frameHeight)); //translates the rectangle to the correct frame to draw.
	return rect;
}





