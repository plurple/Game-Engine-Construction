#include "Background.h"



Background::Background(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
	animated = false;
}


Background::~Background()
{
}

void Background::Update()
{
	//nothing
}
