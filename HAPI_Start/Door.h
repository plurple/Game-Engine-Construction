#pragma once
#include "worldEntity.h"

class Door : public WorldEntity
{
public:
	Door(std::string name, int framesX = 1, int frameNum = 0);
	~Door();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const { return Tag::DOOR; }

	void Update() {}
};

