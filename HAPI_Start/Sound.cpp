#include "Sound.h"



Sound::Sound()
{
}


Sound::~Sound()
{
}

void Sound::LoadSound(std::string name)
{
	if (!HAPI.LoadSound(name))
	{
		
	}
}

void Sound::PlaySound(std::string name)
{
	if (!HAPI.PlaySound(name))
	{
	
	}
}
