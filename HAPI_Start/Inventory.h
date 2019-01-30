#pragma once
#include "GameState.h"

class Graphics;
class World;
class WorldEntity;
class Sound;

class Inventory : public GameState
{
public:
	~Inventory();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();



	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound) {}
	void Render(World *game, Graphics *Viz);

	void Add(int i);
	void Remove(int i);

	static Inventory *Instance() { return &inventory; }

protected:
	Inventory() { inv.resize(50); }

private:
	static Inventory inventory;
	std::vector<bool> inv;
};

