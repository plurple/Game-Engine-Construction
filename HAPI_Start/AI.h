#pragma once
#include "vector2D.h"
#include "HAPI_lib.h"

using namespace HAPISPACE;

class Enemy;
class Player;

class AI
{
public:
	AI();
	~AI();

	void Patrol(Enemy &enemy);
	void SetDirection(Enemy &enemy, vector2D dest);
	void SetState(Enemy &enemy, Player &player);
	bool LineOfSight(Enemy &enemy, vector2D playerPos);

private:
	DWORD lastFrameUpdateTime{ 0 };

};

