#include "enemy.h"



Enemy::Enemy(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
}


Enemy::~Enemy()
{

}


void Enemy::Update()
{
	WorldEntity::AnimationStateMachine();
}

void Enemy::Setup(vector2D pos, std::vector<int> frames, MonsterType type, int gol, int dam, int hp, Direction dir, float speeed, bool isAlive)
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
	typeOfMonster = type;
}

vector2D Enemy::GetDirVector()
{
	return dirVector[(int)direction];
}
