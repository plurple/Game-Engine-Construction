#pragma once
#include "worldEntity.h"

class Player;
class Graphics;

enum class Type
{
	MANA,
	HEALTH,
	BORDER
};

class UIBar : public WorldEntity
{
public:
	UIBar(std::string name, int framesX = 1, int frameNum = 0);
	~UIBar();

	Side GetSide() const { return Side::NOTHING; }
	Tag GetTag() const { return Tag::BAR; }
	void Update();

	void SetUp(vector2D pos, Type t, int num, bool live = true);
	void ChangeSize(UIBar *other, Player &player, Graphics &viz);
	int GetBarNum() const { return barNum; }

private:
	Type type;
	int barNum;
};

