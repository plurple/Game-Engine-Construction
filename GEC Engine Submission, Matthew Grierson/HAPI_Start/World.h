#pragma once
#include <vector>
#include "HAPI_lib.h"

using namespace HAPISPACE;

class Graphics;
class GameState;
class Sound;

class World
{
public:
	World();
	~World();

	void Run();

	void ChangeState(GameState *state);
	void PushState(GameState *state);
	void PopState();

private:
	std::vector<GameState*> states;	
	Graphics *Viz{ nullptr };	
	std::shared_ptr<Sound> sound{ nullptr };

	void Initialise();
	void Cleanup();		

	void HandleInput();
	void Update();
	void Render();
	DWORD lastFrameUpdateTime{ 0 };
};

