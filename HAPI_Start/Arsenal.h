#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class Arsenal : public GameState
{
public:
	~Arsenal();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();

	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) {}
	void Render(World *game, Graphics *Viz);

	static Arsenal *Instance() { return &arse; }

protected:
	Arsenal() {}

private:
	static Arsenal arse;
};

