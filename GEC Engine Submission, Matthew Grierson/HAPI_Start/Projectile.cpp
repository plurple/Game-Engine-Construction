#include "Projectile.h"



Projectile::Projectile(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
	if (position.X < -100.0f || position.X > 1100.0f || position.Y > 900.0f || position.Y < -100.0f)
	{
		alive = false;
		SetPosition(vector2D(0.0f, 0.0f));
		SetState(AnimationState::IDLE);
	}
	if (alive)
	{
		DWORD time = HAPI.GetTime();
		if (time - lastFrameUpdateTime > 5000)
		{
			alive = false;
			lastFrameUpdateTime = time;
		}
	}

	WorldEntity::AnimationStateMachine();
}

void Projectile::Setup(vector2D pos, std::vector<int> frames, Side allegiance, float speeed, Direction dir, int dam, AnimationState state, bool isAlive)
{
	DWORD time = HAPI.GetTime();
	lastFrameUpdateTime = time;
	position = pos;
	animationFrames = frames;
	side = allegiance;
	speed = speeed;
	diagonalSpeed = sqrt((speed * speed) * 2.0f) / 2.0f;
	direction = dir;
	damage = dam;
	currentState = state;
	alive = isAlive;
}
