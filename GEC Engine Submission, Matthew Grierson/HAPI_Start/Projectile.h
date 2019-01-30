#pragma once
#include "worldEntity.h"
class Projectile : public WorldEntity
{
public:
	Projectile(std::string name, int framesX, int frameNum = 0);
	~Projectile();

	Side GetSide() const { return side; }
	Tag GetTag() const { return Tag::PROJECTILE; }
	void Update();
	void Setup(vector2D pos, std::vector<int> frames, Side alliegiance, float speeed = 5.0f, Direction dir = Direction::WEST, int dam = -20, AnimationState state = AnimationState::MOVING, bool isAlive = true);

private:
	Side side;
	DWORD lastFrameUpdateTime{ 0 };
};

