#include "World.h"
#include "Graphics.h"
#include "GameState.h"
#include "MenuState.h"
#include "Sound.h"

World::World()
{
}


World::~World()
{
	delete Viz;
	
}

void World::Initialise()
{
	Viz = new Graphics;
	std::shared_ptr<Sound> newSound = std::make_shared<Sound>();

	Viz->CreateSprite("data//background//background.png", "Menu", false);
	Viz->CreateSprite("data//UI//Inventory.png", "Inventory", false);
	Viz->CreateSprite("data//loot//items.png", "key", true, 7, 7);
	Viz->CreateSprite("data//background//continuous//461223127.jpg", "background", false); //creates a background sprite.
	Viz->CreateSprite("data//background//doors.png", "door", true, 3, 4); //creates a background sprite.
	Viz->CreateSprite("data//heroes//male_warrior.png", "player", true, 32, 8); // creates a player sprite.
	//Viz->CreateSprite("data//temporary//alphaThing.tga", "player", true);
	Viz->CreateSprite("data//UI//Health.png", "health", true);
	Viz->CreateSprite("data//UI//Mana.png", "mana", true);
	Viz->CreateSprite("data//UI//UI.png", "UI", true);
	Viz->CreateSprite("data//background//Walls.png", "wall", false, 8, 4);
	Viz->CreateSprite("data//loot//coin_gold.png", "gold", true, 8);
	Viz->CreateSprite("data//loot//coin_silver.png", "silver", true, 8);
	Viz->CreateSprite("data//loot//coin_copper.png", "copper", true, 8);
	Viz->CreateSprite("data//enemies//minotaur.png", "minotaur", true, 64, 8);
	Viz->CreateSprite("data//projectiles//magic//directional//fireball.png", "fireball", true, 8, 8);
	Viz->CreateSprite("data//projectiles//magic//directional//channel.png", "channel", true, 8, 8);
	Viz->CreateSprite("data//projectiles//magic//directional//flame.png", "flame", true, 8, 8);
	Viz->CreateSprite("data//projectiles//magic//directional//icicle_0.png", "icicle", true, 8, 8);
	Viz->CreateSprite("data//projectiles//magic//directional//shock.png", "shock", true, 8, 8);

	sound->LoadSound("Data//Sound//Fireball.wav");

	ChangeState(MenuState::Instance());

}

void World::Cleanup()
{
	while (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	HAPI.Close();
}

void World::ChangeState(GameState *state)
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->Initialise(Viz, sound);
}

void World::PushState(GameState *state)
{
	states.push_back(state);
	states.back()->Initialise(Viz, sound);
}

void World::PopState()
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}
}

void World::HandleInput()
{
	states.back()->HandleInput(this);
}

void World::Update()
{
	states.back()->Update(this, Viz, sound);
}

void World::Render()
{
	states.back()->Render(this, Viz);
}

void World::Run()
{
	Initialise();

	while (HAPI.Update())
	{
		DWORD time = HAPI.GetTime();
		if (time - lastFrameUpdateTime > 30)
		{
			HandleInput();

			Update();

			lastFrameUpdateTime = time;
		}

			Render();
	}

	Cleanup();
}