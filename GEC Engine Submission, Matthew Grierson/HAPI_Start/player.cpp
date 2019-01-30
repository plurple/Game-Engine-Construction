#include "player.h"
#include "HAPI_lib.h"


using namespace HAPISPACE;



Player::Player(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
}


Player::~Player()
{

}

void Player::Update()
{
	if (!singleAnimation)
	{
		InputHandling();
	}
	
	WorldEntity::AnimationStateMachine();
}

void Player::Setup(vector2D pos, std::vector<int> frames, int gol, int dam, int hp, Direction dir, float speeed, bool isAlive)
{
	position = pos;
	animationFrames = frames;
	speed = speeed;
	diagonalSpeed = sqrt((speed * speed) * 2.0f) / 2.0f;
	direction = dir;
	damage = dam;
	alive = isAlive;
	gold = gol;
	health = hp;
}

void Player::InputHandling()
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	static const HAPI_TMouseData &mouseData = HAPI.GetMouseData();
	const HAPI_TControllerData &data = HAPI.GetControllerData(0);

	int xDirection{ 0 };
	int yDirection{ 0 };
	bool attack{ false }, block{ false }, magic{ false }, throwing{ false }, heal{ false };

	if (data.isAttached)
	{
		int left = (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -10000);
		int right = (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 10000);
		int up = (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000);
		int down = (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000);
		xDirection = right - left;
		yDirection = down - up;
		if (data.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > 0)
			attack = true;
		else if (data.analogueButtons[HK_ANALOGUE_LEFT_TRIGGER] > 0)
			block = true;
		else if (data.digitalButtons[HK_DIGITAL_A])
			interacting = true;
		else if (data.digitalButtons[HK_DIGITAL_X])
			magic = true;
		else if (data.digitalButtons[HK_DIGITAL_B])
			throwing = true;
		else if (data.digitalButtons[HK_DIGITAL_Y])
			heal = true;
		else
		{
			attack = false;
			block = false;
			magic = false;
			interacting = false;
			heal = false;
		}
	}

	int xDirectionkey = keyData.scanCode['D'] - keyData.scanCode['A'];
	int yDirectionkey = keyData.scanCode['S'] - keyData.scanCode['W'];
	bool attackB = mouseData.leftButtonDown;
	bool blockB = mouseData.rightButtonDown;
	bool magicB = keyData.scanCode['1'];
	bool throwingB = keyData.scanCode['2'];
	bool healing = keyData.scanCode['3'];
	interacting = keyData.scanCode['F'];

	
	
	if ((xDirection < 0 && yDirection == 0) || (xDirectionkey < 0 && yDirectionkey == 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::WEST;
	}
	else if ((xDirection < 0 && yDirection < 0) || (xDirectionkey < 0 && yDirectionkey < 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::NORTHWEST;
	}
	else if ((xDirection < 0 && yDirection > 0) || (xDirectionkey < 0 && yDirectionkey > 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::SOUTHWEST;
	}
	else if ((xDirection > 0 && yDirection == 0) || (xDirectionkey > 0 && yDirectionkey == 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::EAST;
	}
	else if ((xDirection > 0 && yDirection < 0) || (xDirectionkey > 0 && yDirectionkey < 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::NORTHEAST;
	}
	else if ((xDirection > 0 && yDirection > 0) || (xDirectionkey > 0 && yDirectionkey > 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::SOUTHEAST;
	}
	else if ((xDirection == 0 && yDirection < 0) || (xDirectionkey == 0 && yDirectionkey < 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::NORTH;
	}
	else if ((xDirection == 0 && yDirection > 0) || (xDirectionkey == 0 && yDirectionkey > 0))
	{
		currentState = AnimationState::MOVING;
		direction = Direction::SOUTH;
	}
	else if (attack || attackB)
	{
		currentState = AnimationState::ATTACK;
	}
	else if (healing || heal)
	{
		
		ChangeHealth(20);
		ChangeMana(-10);
		
		healing = false;
		heal = false;
	}
	else if (magic || magicB)
	{
		currentState = AnimationState::MAGIC;
	}
	else if (throwing || throwingB)
	{
		currentState = AnimationState::THROW;
	}
	else if (block || blockB)
	{
		currentState = AnimationState::BLOCK;
	}
	else
	{
		currentState = AnimationState::IDLE;
	}
}
