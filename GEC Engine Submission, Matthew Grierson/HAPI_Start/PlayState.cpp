#include "PlayState.h"
#include "worldEntity.h"
#include "player.h"
#include "Background.h"
#include "Projectile.h"
#include "Graphics.h"
#include "GameOver.h"
#include "PauseMenu.h"
#include "Inventory.h"
#include "UIBar.h"
#include "Arsenal.h"
#include "MapState.h"
#include "Room.h"

PlayState PlayState::play;

PlayState::~PlayState()
{
}

void PlayState::Cleanup()
{
	
	for (int i = 0; i < 50; i++)
	{
		Inventory::Instance()->Remove(i);
	}
	objects.clear();
	buttons.clear();
	projectiles.clear();
	bars.clear();
}

void PlayState::Initialise(Graphics *Viz, std::shared_ptr<Sound> sound)
{
	std::shared_ptr<UIBar> newUI = std::make_shared<UIBar>("health");
	objects.push_back(newUI);
	bars.push_back(newUI);
	newUI->SetUp(vector2D(100.0, 800.0), Type::HEALTH, 0);
	std::shared_ptr<UIBar> newUI1 = std::make_shared<UIBar>("mana");
	objects.push_back(newUI1);
	bars.push_back(newUI1);
	newUI1->SetUp(vector2D(550.0, 800.0), Type::MANA, 1);
	std::shared_ptr<UIBar> newUI2 = std::make_shared<UIBar>("UI");
	objects.push_back(newUI2);
	bars.push_back(newUI2);
	newUI2->SetUp(vector2D(97.0, 797.0), Type::BORDER, 0);
	std::shared_ptr<UIBar> newUI3 = std::make_shared<UIBar>("UI");
	objects.push_back(newUI3);
	bars.push_back(newUI3);
	newUI3->SetUp(vector2D(547.0, 797.0), Type::BORDER, 1);

	std::shared_ptr<Background> newBackground = std::make_shared<Background>("background");
	objects.push_back(newBackground);
	newBackground->ChangePosition(vector2D(50.0, 15.0));
	newBackground->SetAlive();
		
	std::shared_ptr<Player> newPlayer = std::make_shared<Player>("player", 32, 0);
	objects.push_back(newPlayer);
	newPlayer->Setup(vector2D(400.0, 350.0), std::vector<int>{0, 4, 12, 16, 18, 20, 24, 28, 32});
	player = newPlayer;

	std::shared_ptr<Room> newRoom = std::make_shared<Room>();
	room = newRoom;
	room->CreateRoom(player);	
}

void PlayState::HandleInput(World *game)
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &data = HAPI.GetControllerData(0);


	if (keyData.scanCode[HK_ESCAPE] || data.digitalButtons[HK_DIGITAL_SELECT])
	{
		interaction = true;
	}
	if (interaction && (!keyData.scanCode[HK_ESCAPE] || !data.digitalButtons[HK_DIGITAL_SELECT]))
	{
		interaction = false;
		game->PushState(PauseMenu::Instance());
	}
	else if (keyData.scanCode['I'] || data.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER])
	{
		IPressed = true;
	}
	if (IPressed && (!keyData.scanCode['I'] || !data.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER]))
	{
		IPressed = false;
		game->PushState(Inventory::Instance());
	}
	else if (keyData.scanCode['C'] || data.digitalButtons[HK_DIGITAL_LEFT_SHOULDER])
	{
		IPressed = true;
	}
	if (IPressed && (!keyData.scanCode['C'] || !data.digitalButtons[HK_DIGITAL_LEFT_SHOULDER]))
	{
		IPressed = false;
		game->PushState(Arsenal::Instance());
	}
	else if (keyData.scanCode['M'] || data.digitalButtons[HK_DIGITAL_DPAD_LEFT])
	{
		IPressed = true;
	}
	if (IPressed && (!keyData.scanCode['M'] || !data.digitalButtons[HK_DIGITAL_DPAD_LEFT]))
	{
		IPressed = false;
		game->PushState(MapState::Instance());
	}

}

void PlayState::Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound)
{
	HAPI.SetShowFPS(true, 100);
	
	for (size_t i = 0; i < bars.size(); i++)
	{
		if (bars[i]->GetAlive())
		{
			for (size_t j = 0; j < bars.size(); j++)
			{
				if (i != j && bars[j]->GetAlive() && bars[i]->GetBarNum() == bars[j]->GetBarNum())
				{
					bars[i]->ChangeSize(bars[j].get(), *player, *Viz);
				}
			}
		}
	}

	room->Update(game, Viz, player.get(), sound);
		
	if (player->GetExiting())
	{
		ChangeRoom();
	}

	if (!player->GetAlive())
		game->ChangeState(GameOver::Instance());

}

void PlayState::Render(World *game, Graphics *Viz)
{
	Viz->clearScreen(255);
	for (auto p : objects)
	{
		room->Render(game, Viz);

		if (p->GetTag() == Tag::PLAYER)
		{
			HAPI.RenderText(850, 0, HAPI_TColour(218, 165, 32), "Gold:" + std::to_string(player->GetGold()), 30);
			HAPI.RenderText(32, 800, HAPI_TColour::BLACK, "Health:", 20);
			HAPI.RenderText(250, 800, HAPI_TColour::BLACK, std::to_string(player->GetHealth()) + "/" + std::to_string(player->GetMaxHealth()), 20);
			HAPI.RenderText(490, 800, HAPI_TColour::BLACK, "Mana:", 20);
			HAPI.RenderText(700, 800, HAPI_TColour::BLACK, std::to_string((int)player->GetMana()) + "/" + std::to_string((int)player->GetMaxMana()), 20);
		}
		
		p->Render(*Viz);
	}

}

void PlayState::ChangeRoom()
{
	room->Cleanup();
	player->SetExiting(false);
	Direction dir = player->GetDir();
	if (dir == Direction::NORTH)
	{
		player->SetPosition(vector2D(390.0f, 600.0f));
	}
	else if (dir == Direction::SOUTH)
	{
		player->SetPosition(vector2D(390.0f, 20.0f));
	}
	else if (dir == Direction::EAST)
	{
		player->SetPosition(vector2D(70.0f, 340.0f));
	}
	else if (dir == Direction::WEST)
	{
		player->SetPosition(vector2D(660.0f, 340.0f));
	}
	
	room->CreateRoom(player);
}