#include "Wall.h"



Wall::Wall(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
	animated = false;
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//stuff
}