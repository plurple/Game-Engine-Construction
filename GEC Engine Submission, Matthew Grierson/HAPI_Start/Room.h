#pragma once
#include <vector>
#include "HAPI_lib.h"

class World;
class Graphics;
class WorldEntity;
class Enemy;
class Projectile;
class AI;
class Player;
class Sound;


class Room
{
public:
	Room() {}
	~Room();

	void CreateRoom(std::shared_ptr<Player> player);
	void Cleanup();

	void Update(World *game, Graphics *Viz, Player *player, std::shared_ptr<Sound> sound);
	void Render(World *game, Graphics *Viz);

private:
	AI *ArtificialIntelligence{ nullptr };

	//std::vector<std::string> enemyNames;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Projectile>> projectiles;
	std::vector<std::shared_ptr<WorldEntity>> objects;

};

