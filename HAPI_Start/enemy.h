#pragma once
#include "worldEntity.h"

enum class MonsterType
{
	MELEE,
	RANGED,
	RANDOM
};

class Enemy :	public WorldEntity
{
public:
	Enemy(std::string name, int framesX, int frameNum = 0);
	~Enemy();

	Side GetSide() const { return Side::FOE; }
	Tag GetTag() const { return Tag::ENEMY; }
	void Update();
	void Setup(vector2D pos, std::vector<int> frames, MonsterType type, int gol = 0, int dam = -20, int hp = 50, Direction dir = Direction::WEST, float speeed = 5.0f, bool isAlive = true);

	int GetPoint() const { return currentPoint; }
	std::vector<vector2D> GetPatrol() const { return patrolPoints; }
	MonsterType GetType() const { return typeOfMonster; }
	vector2D GetDirVector();

	void SetCurrentPatrolPoint(int point) { currentPoint = point; }
	

private:
	
	int currentPoint{ 0 };
	MonsterType typeOfMonster{ MonsterType::MELEE};
	std::vector<vector2D> dirVector{ {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {-1.0f, 1.0f}, {-1.0f, 0.0f}, {-1.0f, -1.0f}, {0.0, -1.0f}, {1.0f, -1.0f} };
	std::vector<vector2D> patrolPoints{ {500.0f, 300.0f}, {300.0f, 200.0f}, {500.0f, 200.0f}, {400.0f, 200.0f}, {200.0f, 600.0f}, {300.0f, 200.0f}, {200.0f, 100.0f} };
};

