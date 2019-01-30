#include "Arsenal.h"
#include "World.h"
#include "Graphics.h"
#include "Background.h"
#include "Button.h"
#include "Sound.h"

Arsenal Arsenal::arse;

Arsenal::~Arsenal()
{
}

void Arsenal::Cleanup()
{
	objects.clear();
	buttons.clear();
}

void Arsenal::Initialise(Graphics *Viz, std::shared_ptr<Sound> sound)
{
	std::shared_ptr<Background> newBackground = std::make_shared<Background>("Inventory");
	objects.push_back(newBackground);
	newBackground->SetPosition(vector2D(400.0, 200.0));
	newBackground->SetAlive();
}

void Arsenal::HandleInput(World *game)
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

void Arsenal::Render(World *game, Graphics *Viz)
{
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