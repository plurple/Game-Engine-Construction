#pragma once
#include "worldEntity.h"

class Wall : public WorldEntity
{
public:
	Wall(std::string name, int framesX = 1, int frameNum = 0);
	~Wall();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const { return Tag::WALL; }
	void Update();
};

