#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class MenuState : public GameState
{
public:
	~MenuState();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();

	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound);
	void Render(World *game, Graphics *Viz);	

	static MenuState *Instance() { return &menu; }

protected:
	MenuState() {}

private:
	static MenuState menu;	
};

