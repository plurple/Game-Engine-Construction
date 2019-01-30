#include "GameOver.h"
#include "World.h"
#include "Graphics.h"
#include "Background.h"
#include "Button.h"

GameOver GameOver::gameOver;

GameOver::~GameOver()
{
}

void GameOver::Cleanup()
{
	objects.clear();
	buttons.clear();
}

void GameOver::Initialise(Graphics *Viz, std::shared_ptr<Sound> sound)
{

	std::shared_ptr<Background> newBackground = std::make_shared<Background>("Menu");
	objects.push_back(newBackground);
	newBackground->ChangePosition(vector2D(0.0, 0.0));
	newBackground->SetAlive();

	std::shared_ptr<Button> newButton2 = std::make_shared<Button>("Main Menu", vector2D(400, 500), Rectangle(210, 50));
	buttons.push_back(newButton2);
}

void GameOver::HandleInput(World *game)
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	static const HAPI_TMouseData &mouseData = HAPI.GetMouseData();
	const HAPI_TControllerData &data = HAPI.GetControllerData(0);

	int X = mouseData.x;
	int Y = mouseData.y;

	for (auto butt : buttons)
	{
		Rectangle buttRect = butt->GetRect();
		vector2D buttPos = butt->GetPosition();
		buttRect.Translate((int)buttPos.X, (int)buttPos.Y);
		if (X < buttRect.right && X > buttRect.left && Y < buttRect.bottom && Y > buttRect.top)
		{
			butt->SetCol(HAPI_TColour(120, 50, 190));
			if (mouseData.leftButtonDown)
			{
				mousePressed = true;
			}
			if (mousePressed && !mouseData.leftButtonDown)
			{
				mousePressed = false;
				std::string name = butt->GetName();
				if (name == "Main Menu")
				{
					game->PopState();
				}
			}
		}
		else
			butt->SetCol(HAPI_TColour::WHITE);
	}

	if (keyData.scanCode['W'] || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000)
	{
		MoveUp();
	}
	else if (keyData.scanCode['S'] || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000)
	{
		MoveDown();
	}

	if (keyData.scanCode['F'] || data.digitalButtons[HK_DIGITAL_A])
	{
		interaction = true;
	}
	if (interaction && (!keyData.scanCode['F'] || !data.digitalButtons[HK_DIGITAL_A]))
	{
		interaction = false;
		std::string name = buttons[currentButton]->GetName();
		if (name == "Main Menu")
		{
			game->PopState();
		}
	}
}

void GameOver::Render(World *game, Graphics *Viz)
{
	Viz->clearScreen(0);
	for (auto p : objects)
	{
		p->Render(*Viz);
	}

	for (auto butt : buttons)
	{
		vector2D pos = butt->GetPosition();
		HAPI.RenderText((int)pos.X, (int)pos.Y, butt->GetCol(), butt->GetName(), 40);
	}
}