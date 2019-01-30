#include "Door.h"


Door::Door(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
	animated = false;
}


Door::~Door()
{
}
