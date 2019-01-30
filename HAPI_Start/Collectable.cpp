#include "Collectable.h"



Collectable::Collectable(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
}


Collectable::~Collectable()
{
}

void Collectable::Update()
{

}

void Collectable::Setup(vector2D pos, std::vector<int> frames, int gol, bool isAlive) 
{
	position = pos;
	animationFrames = frames;
	gold = gol;
	alive = isAlive;
}
