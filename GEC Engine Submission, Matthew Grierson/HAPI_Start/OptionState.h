#pragma once
#include "GameState.h"

class WorldEntity;
class World;
class Graphics;
class sound;

class OptionState : public GameState
{
public:
	~OptionState();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();


	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound);
	void Render(World *game, Graphics *Viz);

	static OptionState *Instance() { return &option; }

protected:
	OptionState() {}

private:
	static OptionState option;
};

