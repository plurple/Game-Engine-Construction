#pragma once
#include <unordered_map>
#include "HAPI_lib.h"

using namespace HAPISPACE;


class Sound
{
public:
	Sound();
	~Sound();

	void LoadSound(std::string name);
	void PlaySound(std::string name);

};

