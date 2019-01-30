#include "Inventory.h"
#include "World.h"
#include "Graphics.h"
#include "Background.h"
#include "Button.h"
#include "KeyItemBase.h"

Inventory Inventory::inventory;

Inventory::~Inventory()
{
	inv.clear();
}

void Inventory::Cleanup()
{
	objects.clear();
	buttons.clear();
}

void Inventory::Initialise(Graphics *Viz, std::shared_ptr<Sound> sound)
{
	std::shared_ptr<Background> newBackground = std::make_shared<Background>("Inventory");
	objects.push_back(newBackground);
	newBackground->SetPosition(vector2D(400.0, 200.0));
	newBackground->SetAlive();

	for (int i = 0; i < 50; i++)
	{
		std::shared_ptr<KeyItemBase> newKey = std::make_shared<KeyItemBase>("key", 7, i);
		objects.push_back(newKey);
		if (inv[i] == true)
		{
			float X = 400.0f + ((newKey->GetFrame() % 7) * newKey->GetRect(*Viz).CalculateWidth());
			float Y = 248.0f + ((newKey->GetFrame() / 7) * newKey->GetRect(*Viz).CalculateHeight());
			
			newKey->Setup(vector2D(X, Y), { 0, 0 }, 0, true);
		}
	}
}

void Inventory::HandleInput(World *game)
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

void Inventory::Render(World *game, Graphics *Viz)
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

void Inventory::Add(int i)
{
	inv[i] = true;
}

void Inventory::Remove(int i)
{
	inv[i] = false;
}
