#pragma once
#include "worldEntity.h"



class Player :	public WorldEntity
{
public:
	Player(std::string name, int framesX, int frameNum = 0);
	~Player();

	void InputHandling();

	Side GetSide() const { return Side::FRIEND; }
	Tag GetTag() const override final { return Tag::PLAYER; }
	void Update() override final;	
	void Setup(vector2D pos, std::vector<int> frames, int gol = 0, int dam = -20, int hp = 100, Direction dir = Direction::WEST, float speeed = 5.0f, bool isAlive = true);
};

