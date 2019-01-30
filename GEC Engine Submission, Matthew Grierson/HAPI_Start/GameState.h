#pragma once
#include "World.h"

class Graphics;
class Button;
class WorldEntity;
class Sound;

class GameState
{
public:
	virtual void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound) = 0;
	virtual void Cleanup() = 0;


	virtual void HandleInput(World *game) = 0;
	virtual void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) = 0;
	virtual void Render(World *game, Graphics *Viz) = 0;
	
	void MoveUp();
	void MoveDown();

	void ChangeState(World *game, GameState* state) { game->ChangeState(state); }

protected:
	GameState() { }
	std::vector<std::shared_ptr<Button>> buttons;
	int currentButton{ 0 };
	std::vector<std::shared_ptr<WorldEntity>> objects;
	bool mousePressed{ false };
	bool interaction{ false };
	bool IPressed{ false };
	
};

