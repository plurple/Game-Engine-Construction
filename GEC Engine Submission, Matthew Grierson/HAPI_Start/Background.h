#pragma once
#include "worldEntity.h"
class Background :	public WorldEntity
{
public:
	Background(std::string name, int framesX = 1, int frameNum = 0);
	~Background();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const { return Tag::NEUTRAL; }
	void Update();
};

