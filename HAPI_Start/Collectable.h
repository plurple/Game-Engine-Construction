#pragma once
#include "worldEntity.h"
class Collectable :	public WorldEntity
{
public:
	Collectable(std::string name, int framesX, int frameNum = 0);
	~Collectable();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const override final { return Tag::COLLECTABLE; }
	void Update() override final;
	void Setup(vector2D pos, std::vector<int> frames, int gol = 5, bool isAlive = true);
};

