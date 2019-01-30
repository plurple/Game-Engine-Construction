#pragma once
#include "GameState.h"

class Graphics;
class WorldEntity;
class Projectile;
class Player;
class UIBar;
class Room;
class Sound;

class PlayState : public GameState
{
public:
	~PlayState();

	void Initialise(Graphics *Viz, std::shared_ptr<Sound> sound);
	void Cleanup();


	void HandleInput(World *game);
	void Update(World *game, Graphics *Viz, std::shared_ptr<Sound> sound);
	void Render(World *game, Graphics *Viz);
	void ChangeRoom();

	
	static PlayState *Instance() { return &play; }

protected:
	PlayState() {}

private:
	static PlayState play;

	std::shared_ptr<Room> room;

	std::shared_ptr<Player> player{ nullptr };
	std::vector<std::shared_ptr<Projectile>> projectiles;
	std::vector<std::shared_ptr<UIBar>> bars;
};

