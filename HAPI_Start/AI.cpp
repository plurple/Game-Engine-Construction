#include "AI.h"
#include <vector>
#include "enemy.h"
#include "player.h"


AI::AI()
{
}


AI::~AI()
{
}

void AI::SetState(Enemy &enemy, Player &player)
{

	float dist = enemy.GetPosition().Dist(player.GetPosition()).length();
	bool Alive = player.GetAlive();
	MonsterType type = enemy.GetType();

	
	switch (type)
	{
	case MonsterType::MELEE:
	{
		if (dist < 60.0f && Alive)
		{
			enemy.SetState(AnimationState::ATTACK);
		}
		else if (dist < 300.0f && Alive)
		{
			SetDirection(enemy, player.GetPosition());
		}
		else
		{
			Patrol(enemy);
		}
		break;
	}
	case MonsterType::RANDOM:
	{
		DWORD time = HAPI.GetTime();
		if (time - lastFrameUpdateTime > 200)
		{
			int dir = rand() % 7;
			enemy.SetDir((Direction)dir);
			enemy.SetState(AnimationState::MOVING);
			lastFrameUpdateTime = time;
		}
		break;
	}
	case MonsterType::RANGED:
	{
		bool lOS = LineOfSight(enemy, player.GetPosition());
		DWORD time = HAPI.GetTime();
		if (lOS && time - lastFrameUpdateTime > 200)
		{
			enemy.SetState(AnimationState::MAGIC);
			lastFrameUpdateTime = time;
		}
		else if (!lOS)
		{
			Patrol(enemy);
		}
		break;
	}
	}

}

void AI::Patrol(Enemy &enemy)
{
	std::vector<vector2D> points = enemy.GetPatrol();
	int currentPoint = enemy.GetPoint();
	if (points.size() > 0)
	{
		if (enemy.GetPosition().Dist(points[currentPoint]).length() < 10.0f)
		{
			currentPoint++;
			if (currentPoint >= points.size())
				currentPoint = 0;

			enemy.SetCurrentPatrolPoint(currentPoint);
		}
		SetDirection(enemy, points[currentPoint]);
	}
}

void AI::SetDirection(Enemy &enemy, vector2D dest)
{
	enemy.SetState(AnimationState::MOVING);
	float speed = enemy.GetSpeed();
	vector2D pos = enemy.GetPosition();
	if (dest.X < pos.X - speed && dest.Y < pos.Y - speed)
	{
		enemy.SetDir(Direction::NORTHWEST);
	}
	else if (dest.X < pos.X - speed && dest.Y > pos.Y + speed)
	{
		enemy.SetDir(Direction::SOUTHWEST);
	}

	else if (dest.X > pos.X + speed && dest.Y < pos.Y - speed)
	{
		enemy.SetDir(Direction::NORTHEAST);
	}
	else if (dest.X > pos.X + speed && dest.Y > pos.Y + speed)
	{
		enemy.SetDir(Direction::SOUTHEAST);
	}
	else if (dest.X < pos.X - speed && (dest.Y > pos.Y - speed || dest.Y < pos.Y + speed))
	{
		enemy.SetDir(Direction::WEST);
	}
	else if (dest.X > pos.X + speed && (dest.Y > pos.Y - speed || dest.Y < pos.Y + speed))
	{
		enemy.SetDir(Direction::EAST);
	}
	else if ((dest.X < pos.X + speed || dest.X > pos.X - speed) && dest.Y < pos.Y - speed)
	{
		enemy.SetDir(Direction::NORTH);
	}
	else if ((dest.X < pos.X + speed || dest.X > pos.X - speed) && dest.Y > pos.Y + speed)
	{
		enemy.SetDir(Direction::SOUTH);
	}

}

bool AI::LineOfSight(Enemy &enemy, vector2D playerPos)
{
	vector2D distanceBetween = playerPos.Dist(enemy.GetPosition());


	distanceBetween.normalize();
	float dot = ((int)((distanceBetween.DotProduct(enemy.GetDirVector())) * 100 + .5) / 100.0f);
	if (dot == 1)
		return true;

	return false;
}