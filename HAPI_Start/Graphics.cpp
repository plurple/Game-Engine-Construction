#include "Graphics.h"
#include "Sprite.h"



Graphics::Graphics()
{
	//create the window
	if (!HAPI.Initialise(screenWidth, screenHeight))
	{
		return;
	}
	screen = HAPI.GetScreenPointer(); // gets the pointer to the start of the screen.

}


Graphics::~Graphics()
{

}

void Graphics::clearScreen(int col)
{
	//clears the screen to black.
	BYTE *pnter = screen;
	memset(screen, col, screenHeight * screenWidth * 4);
}

void Graphics::changePixel(BYTE *pnter, HAPI_TColour colour)
{
	memcpy(pnter, &colour, 4);
}


void Graphics::CreateSprite(const std::string &filename, const std::string &uniqueName, bool alpha, int numberOfFramesX, int numberOfFramesY)
{
	//creates a sprite and then adds it to the collection of sprites.
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(filename, alpha, numberOfFramesX, numberOfFramesY);
	spriteMap[uniqueName] = sprite;

}

void Graphics::RenderSprite(const std::string &uniqueName, vector2D screenPos, int frameNumber)
{
	//checks to make sure that the specified sprite exists.
	if (spriteMap.find(uniqueName) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + uniqueName, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();

	}

	std::shared_ptr<Sprite> sprite = spriteMap.at(uniqueName);
	Rectangle spriteSpace = sprite->GetRect(); //creates a rectangle for the sprite for clipping purposes.

	int screenX = (int)screenPos.X;
	int screenY = (int)screenPos.Y;

	spriteSpace.Translate(screenX, screenY); //translates the sprite to screen space.
	//checks if the sprite is completly within the screen.
	if (spriteSpace.CompletelyContains(screenSpace))
	{
		spriteSpace.Translate(-screenX, -screenY); //translates sprite back into it's own space.


		sprite->Blit(screen, screenWidth, screenX, screenY, spriteSpace, frameNumber);


	}
	//makes sure the sprite isn't completly off screen if so doesn't draw it.
	else if (!spriteSpace.CompletelyOutside(screenSpace))
	{
		spriteSpace.ClipTo(screenSpace);
		spriteSpace.Translate(-screenX, -screenY);//translates back to sprite space.
		//check if sprite is off the left Tag of the screen
		if (screenX < 0)
		{
			//adjusts the sprite's x position so it can move the sprite pointer.
			screenX = 0;
		}
		//check if sprite is off the top Tag of the screen
		if (screenY < 0)
		{
			//adjusts the sprite's y position so it can move the sprite pointer.
			screenY = 0;
		}

		//passes information to the sprite class so that it can be drawn.

		sprite->Blit(screen, screenWidth, screenX, screenY, spriteSpace, frameNumber);

	}
}

void Graphics::SetSpriteWidth(std::string name, int newWidth)
{
	if (spriteMap.find(name) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + name, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}

	spriteMap.at(name)->SetWidth(newWidth);
}

Rectangle Graphics::GetSpriteRect(std::string name)
{
	if (spriteMap.find(name) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + name, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}

	return spriteMap.at(name)->GetRect();
}

Rectangle Graphics::GetSpriteFrameRect(std::string name, Rectangle rect, int frameNumber)
{
	if (spriteMap.find(name) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + name, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}

	return spriteMap.at(name)->GetFrameRect(rect, frameNumber);
}

BYTE* Graphics::GetSpritePnter(std::string name)
{
	if (spriteMap.find(name) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + name, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}

	return spriteMap.at(name)->GetPnter();
}

int Graphics::GetSpriteWidth(std::string name)
{
	if (spriteMap.find(name) == spriteMap.end())
	{
		HAPI_UserResponse responce;
		HAPI.UserMessage("Sprite not found", "Missing " + name, HAPI_ButtonType::eButtonTypeOk, &responce);
		if (responce == HAPI_UserResponse::eUserResponseOk)
			HAPI.Close();
	}

	return spriteMap.at(name)->GetSpriteWidth();
}
