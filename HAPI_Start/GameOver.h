#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class GameOver : public GameState
{
public:
	~GameOver();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();

	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) {}
	void Render(World *game, Graphics *Viz);

	static GameOver *Instance() { return &gameOver; }

protected:
	GameOver() {}

private:
	static GameOver gameOver;
};

