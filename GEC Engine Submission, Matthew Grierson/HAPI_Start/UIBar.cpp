#include "UIBar.h"
#include "player.h"
#include "Graphics.h"



UIBar::UIBar(std::string name, int framesX, int frameNum) : WorldEntity(name, framesX, frameNum)
{
	animated = false;
}


UIBar::~UIBar()
{
}

void UIBar::Update()
{

}

void UIBar::SetUp(vector2D pos, Type t, int num, bool live)
{
	position = pos;
	type = t;
	barNum = num;
	alive = live;
}

void UIBar::ChangeSize(UIBar *other, Player &player, Graphics &viz)
{
	switch (type)
	{
	case Type::HEALTH:
	{
		float healthPercentage = (float)player.GetHealth() / (float)player.GetMaxHealth();
		float newWidth = viz.GetSpriteWidth(spriteName) * healthPercentage;
		viz.SetSpriteWidth(spriteName, (int)newWidth);
		break;
	}
	case Type::MANA:
	{
		float manaPercentage = (float)player.GetMana() / (float)player.GetMaxMana();
		float newWidth = viz.GetSpriteWidth(spriteName) * manaPercentage;
		viz.SetSpriteWidth(spriteName, (int)newWidth);
		break;
	}
	}
		


}