#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class PauseMenu : public GameState
{
public:
	~PauseMenu();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();


	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) {}
	void Render(World * game, Graphics *Viz);

	static PauseMenu *Instance() { return &pause; }

protected:
	PauseMenu() {}

private:
	static PauseMenu pause;
};

