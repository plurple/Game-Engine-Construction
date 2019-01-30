#pragma once
#include "worldEntity.h"
class KeyItemBase :	public WorldEntity
{
public:
	KeyItemBase(std::string name, int framesX = 1, int frameNum = 0);
	~KeyItemBase();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const { return Tag::KEY; }
	void Update();

	void Setup(vector2D pos, std::vector<int> frames, int gol = 0, bool isAlive = true);
};

