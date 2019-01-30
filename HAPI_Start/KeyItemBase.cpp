#include "KeyItemBase.h"



KeyItemBase::KeyItemBase(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
	animated = false;
}


KeyItemBase::~KeyItemBase()
{
}

void KeyItemBase::Update()
{

}

void KeyItemBase::Setup(vector2D pos, std::vector<int> frames, int gol, bool isAlive)
{
	position = pos;
	animationFrames = frames;
	gold = gol;
	alive = isAlive;
}
