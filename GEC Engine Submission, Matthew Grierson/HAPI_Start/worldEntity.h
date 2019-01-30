#pragma once
#include <vector>
#include "vector2D.h"
#include <string>
#include "HAPI_lib.h"
#include "Rectangle.h"

using namespace HAPISPACE;

enum class Tag
{
	PLAYER,
	ENEMY,
	PROJECTILE,
	NEUTRAL,
	WALL,
	COLLECTABLE,
	KEY,
	BAR,
	DOOR
};

enum class Side
{
	FRIEND,
	FOE,
	NOTHING
};

enum class AnimationState
{
	IDLE,
	MOVING,
	ATTACK,
	BLOCK,
	GETHIT,
	DIE,
	MAGIC,
	THROW
};

enum class Direction
{
	WEST,
	NORTHWEST,
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST
};

class Graphics;

class WorldEntity
{
public:
	WorldEntity(std::string name, int framesX, int frameNum);
	

	virtual void Update() = 0;
	void Collision(WorldEntity *other, Graphics &viz);
	void Render(Graphics &viz);
	bool RectangleCollision(WorldEntity *other, Graphics &viz);
	void AnimationStateMachine();
	void Animation();
	
	void ChangePosition(vector2D newPos);
	void ChangeHealth(int amount);
	void ChangeMana(float amount);

	void SetAlive() { alive = !alive; }
	void SetShooting() { isShooting = !isShooting; }
	void SetExiting(bool a) { exiting = a; }
	void SetName(std::string name);
	void SetState(AnimationState newState) { currentState = newState; }
	void SetDir(Direction dir) { direction = dir; }
	void SetPosition(vector2D newPos) { position = newPos; }


	virtual Tag GetTag() const = 0;
	virtual Side GetSide() const = 0;
	vector2D GetPosition() const { return position; }
	Rectangle GetRect(Graphics &viz) const;
	int GetGold() const { return gold; }
	bool GetAlive() const { return alive; }
	std::string GetName() const { return spriteName; }
	int GetHealth() const { return health; }
	int GetMaxHealth() const { return maxHealth; }
	float GetMaxMana() const { return maxMana; }
	float GetMana() const { return mana; }
	int GetFrame() const { return frameNumber; }
	bool GetSingle() const { return singleAnimation; }
	bool GetShooting() const { return isShooting; }
	bool GetExiting() const { return exiting; }
	Direction GetDir() const { return direction; }
	vector2D GetFirePoint();
	float GetSpeed() const { return speed; }
	AnimationState GetState() const { return currentState; }


protected:
	vector2D position, previousPosition;
	std::string spriteName;
	bool alive{ false }, isAttacking{ false };
	bool animated{ true }, interacting{ false }, exiting{ false };
	bool singleAnimation{ false }, isShooting{ false };
	float speed{ 5.0f };
	float diagonalSpeed = sqrt((speed * speed) * 2.0f) / 2.0f;
	Direction direction{ Direction::WEST };
	AnimationState currentState{ AnimationState::IDLE };
	std::vector<int> animationFrames{ 0, 1 };
	std::vector<vector2D> firePoints{ {0.0, 32.0}, {0.0, 0.0}, {32.0, 0.0}, {64.0, 0.0}, {64.0, 32.0}, {64.0, 64.0}, {32.0, 64.0}, {0.0, 64.0} };
	int gold{ 0 }, health{ 100 }, maxHealth{ 100 }, damage{ -50 };
	float mana{ 100 }, maxMana{ 100 };
	DWORD lastFrameUpdateTime{ 0 };
	int frameNumber{ 0 }, numberOfFramesX{ 1 };	
};

