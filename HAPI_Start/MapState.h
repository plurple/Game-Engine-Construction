#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class MapState : public GameState
{
public:
	~MapState();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();

	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) {}
	void Render(World *game, Graphics *Viz);

	static MapState *Instance() { return &map; }

protected:
	MapState() {}

private:
	static MapState map;

};

