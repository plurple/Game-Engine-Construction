#include "MapState.h"
#include "World.h"
#include "Graphics.h"
#include "Background.h"
#include "Button.h"

MapState MapState::map;



MapState::~MapState()
{
}


void MapState::Initialise(Graphics *Viz, std::shared_ptr<Sound> sound)
{

}

void MapState::Cleanup()
{
	objects.clear();
	buttons.clear();
}

void MapState::HandleInput(World *game)
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	static const HAPI_TMouseData &mouseData = HAPI.GetMouseData();
	const HAPI_TControllerData &data = HAPI.GetControllerData(0);

	if (keyData.scanCode['F'] || data.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER])
	{
		interaction = true;
	}
	if (interaction && (!keyData.scanCode['F'] || !data.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER]))
	{
		interaction = false;
		game->PopState();
	}
}

void MapState::Render(World *game, Graphics *Viz)
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