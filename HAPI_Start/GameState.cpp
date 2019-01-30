#include "GameState.h"
#include "Button.h"



void GameState::MoveUp()
{
	if (currentButton != 0)
	{
		buttons[currentButton]->SetCol(HAPI_TColour::WHITE);
		currentButton--;
		buttons[currentButton]->SetCol(HAPI_TColour(120, 50, 190));
	}
}
void GameState::MoveDown()
{
	if (currentButton != buttons.size()-1)
	{
		buttons[currentButton]->SetCol(HAPI_TColour::WHITE);
		currentButton++;
		buttons[currentButton]->SetCol(HAPI_TColour(120, 50, 190));
	}
}