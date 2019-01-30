#include "worldEntity.h"
#include "Graphics.h"
#include "Inventory.h"


WorldEntity::WorldEntity(std::string name, int framesX, int frameNum) : spriteName(name), numberOfFramesX(framesX), frameNumber(frameNum)
{
}



void WorldEntity::Render(Graphics &viz)
{
	if (alive || currentState == AnimationState::DIE)
	{
		if (animated)
		{
			Animation();
		}

		viz.RenderSprite(spriteName, position, frameNumber);
	}
}

void WorldEntity::Animation()
{
	DWORD time = HAPI.GetTime();
	if (time - lastFrameUpdateTime > 100)
	{
		frameNumber++;
		lastFrameUpdateTime = time;
	}
	if (frameNumber < (int)direction * numberOfFramesX + animationFrames[(int)currentState])
	{
		frameNumber = (int)direction * numberOfFramesX + animationFrames[(int)currentState];
	}
	else if (frameNumber > (int)direction * numberOfFramesX + animationFrames[(int)currentState + 1] - 1)
	{
		frameNumber = (int)direction * numberOfFramesX + animationFrames[(int)currentState];
		if (singleAnimation)
		{
			if (GetTag() != Tag::PROJECTILE)
				currentState = AnimationState::IDLE;
			singleAnimation = false;
		}
	}
}

Rectangle WorldEntity::GetRect(Graphics &viz) const
{
	return viz.GetSpriteRect(spriteName);
}

vector2D WorldEntity::GetFirePoint()
{
	return position + firePoints[(int)direction];
}

void WorldEntity::Collision(WorldEntity *other, Graphics &viz)
{
	Tag otherTag = other->GetTag();
	if (RectangleCollision(other, viz))
	{
		Tag tag = GetTag();

		if (tag == Tag::PLAYER && interacting && otherTag == Tag::DOOR)
		{
			//
			exiting = true;
			interacting = false;
		}
		Rectangle rect = GetRect(viz);
		Rectangle otherRect = other->GetRect(viz);
		vector2D otherPosition = other->GetPosition();
		rect.Translate((int)position.X, (int)position.Y);
		otherRect.Translate((int)otherPosition.X, (int)otherPosition.Y);
		rect.ClipTo(otherRect);
		otherRect.ClipTo(rect);
		rect.Translate((int)-position.X, (int)-position.Y);
		otherRect.Translate((int)-otherPosition.X, (int)-otherPosition.Y);

		rect = viz.GetSpriteFrameRect(spriteName, rect, frameNumber);
		int rectWidth = rect.CalculateWidth();
		int rectHeight = rect.CalculateHeight();
		int spriteWidth = viz.GetSpriteWidth(spriteName);
		unsigned int frameCorrection = ((rect.left + rect.top * spriteWidth) * 4);
		BYTE *rectPnter = viz.GetSpritePnter(spriteName) + frameCorrection;

		std::string otherName = other->GetName();
		otherRect = viz.GetSpriteFrameRect(otherName, otherRect, other->GetFrame());
		int otherSpriteWidth = viz.GetSpriteWidth(otherName);
		frameCorrection = ((otherRect.left + otherRect.top * otherSpriteWidth) * 4);
		BYTE *otherRectPnter = viz.GetSpritePnter(otherName) + frameCorrection;

		BYTE alpha, otherAlpha;

		for (int i = 0; i < rectHeight; i++)
		{
			for (int j = 0; j < rectWidth; j++)
			{
				alpha = rectPnter[3];
				otherAlpha = otherRectPnter[3];

				if (alpha > 50 && otherAlpha > 50)
				{
					
					switch (currentState)
					{
					case AnimationState::IDLE:
					{
						if (tag == Tag::PLAYER && other->GetAlive() && interacting)
						{
							if (otherTag == Tag::KEY)
							{
								other->SetAlive();
								//adds to inventory
								Inventory::Instance()->Add(other->GetFrame());
								gold += other->GetGold();
								interacting = false;
							}
						}
						break;
					}
					case AnimationState::MOVING:
					{
						if (otherTag == Tag::WALL || otherTag == Tag::ENEMY || ((tag == Tag::ENEMY || tag == Tag::PROJECTILE) && otherTag == Tag::PLAYER))
						{
							if (tag == Tag::PROJECTILE)
							{
								if (GetSide() != other->GetSide() && other->GetSide() != Side::NOTHING)
								{
									if (alive)
									{
										SetAlive();
										other->ChangeHealth(damage);
										if (other->GetHealth() <= 0)
										{
											other->SetAlive();
										}
									}
									break;
								}
								else if (GetSide() != other->GetSide())
								{
									if (alive)
									{
										SetAlive();
									}
									break;
								}
								break;
							}
							rect = GetRect(viz);
							otherRect = other->GetRect(viz);
							rect.Translate((int)position.X, (int)position.Y);
							int rectWidth = rect.CalculateWidth();
							int rectHeight = rect.CalculateHeight();
							otherRect.Translate((int)otherPosition.X, (int)otherPosition.Y);
							int otherRectWidth = otherRect.CalculateWidth();
							int otherRectHeight = otherRect.CalculateHeight();

							switch (direction)
							{
							case Direction::WEST:
								if ((rect.bottom > otherRect.bottom - otherRectHeight) && (rect.top < otherRect.top + otherRectHeight))
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							case Direction::NORTHWEST:
								if (rect.left < otherRect.right && rect.top > otherRect.bottom - rectHeight/2)
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								else if (rect.top < otherRect.bottom  && rect.left > otherRect.right - rectWidth/2)
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							case Direction::NORTH:
								if ((rect.left < otherRect.left + otherRectWidth) && (rect.right > otherRect.right - otherRectWidth))
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								break;
							case Direction::NORTHEAST:
								if (rect.right > otherRect.left && rect.top > otherRect.bottom - rectHeight/2)
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								else if (rect.top < otherRect.bottom  && rect.right < otherRect.left + rectWidth/2)
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							case Direction::EAST:
								if ((rect.bottom > otherRect.bottom - otherRectHeight) && (rect.top < otherRect.top + otherRectHeight))
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							case Direction::SOUTHEAST:
								if (rect.right > otherRect.left  && rect.bottom < otherRect.top + rectHeight/2)
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								else if (rect.bottom > otherRect.top && rect.right < otherRect.left + rectWidth/2)
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							case Direction::SOUTH:
								if ((rect.left < otherRect.left + otherRectWidth) && (rect.right > otherRect.right - otherRectWidth))
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								break;
							case Direction::SOUTHWEST:
								if (rect.left < otherRect.right && rect.bottom < otherRect.top + rectHeight/2)
								{
									position = vector2D(position.X, previousPosition.Y);
								}
								else if (rect.bottom > otherRect.top  && rect.left > otherRect.right - rectWidth/2)
								{
									position = vector2D(previousPosition.X, position.Y);
								}
								break;
							}
						}
						else if (tag == Tag::PLAYER && other->GetAlive())
						{
							if (otherTag == Tag::COLLECTABLE)
							{
								gold += other->GetGold();
								other->SetAlive();
							}
							else if (otherTag == Tag::KEY && interacting)
							{
								other->SetAlive();
								//add to inventory
								Inventory::Instance()->Add(other->GetFrame());
								gold += other->GetGold();
								interacting = false;
							}
							
						}
						break;
					}
					case AnimationState::ATTACK:
					{
						if (((tag != Tag::ENEMY && otherTag == Tag::ENEMY) || otherTag == Tag::PLAYER) && isAttacking)
						{
							other->ChangeHealth(damage);
							
							isAttacking = false;
							if (other->GetHealth() <= 0)
							{
								gold += other->GetGold();
								other->SetAlive();
							}
						}
						break;
					}
					}
				}
				rectPnter += 4;
				otherRectPnter += 4;
			}
			otherRectPnter += (otherSpriteWidth - rectWidth) * 4;
			rectPnter += (spriteWidth - rectWidth) * 4;
		}

	}
}


void WorldEntity::ChangeHealth(int amount)
{
	if (amount < 0)
	{
		currentState = AnimationState::GETHIT;
	}
	health += amount;
	if (health <= 0)
	{
		currentState = AnimationState::DIE;
	}
	else if (health >= maxHealth)
	{
		health = maxHealth;
	}
}

void WorldEntity::ChangeMana(float amount)
{
	mana += amount;
	if (mana > maxMana)
	{
		mana = maxMana;
	}
	else if (mana < 0)
	{
		mana = 0;
	}
}

void WorldEntity::SetName(std::string name)
{
	spriteName = name;
}

void WorldEntity::ChangePosition(vector2D newPos)
{
	previousPosition = position;
	position += newPos;
}

bool WorldEntity::RectangleCollision(WorldEntity *other, Graphics &viz)
{
	Rectangle rect = GetRect(viz);
	Rectangle otherRect = other->GetRect(viz);
	vector2D otherPosition = other->GetPosition();
	rect.Translate((int)position.X, (int)position.Y);
	otherRect.Translate((int)otherPosition.X, (int)otherPosition.Y);

	if (!rect.CompletelyOutside(otherRect))
	{
		return true;
	}
	return false;
}

void WorldEntity::AnimationStateMachine()
{
	switch (currentState)
	{
	case AnimationState::ATTACK:
	{
		if (!singleAnimation)
			isAttacking = true;
		singleAnimation = true;		
		break;
	}
	case AnimationState::THROW:
	case AnimationState::MAGIC:
	{
		if (mana >= 10)
		{
			if (!singleAnimation)
				isShooting = true;
		}
		else
		{
			currentState = AnimationState::IDLE;
			break;
		}
	}
	case AnimationState::BLOCK:
	case AnimationState::GETHIT:
	case AnimationState::DIE:
	{
		singleAnimation = true;
		break;
	}
	case AnimationState::MOVING:
	{
		switch (direction)
		{
		case Direction::WEST:
		{
			ChangePosition(vector2D(-speed, 0.0f));
			break;
		}
		case Direction::NORTHWEST:
		{
			ChangePosition(vector2D(-diagonalSpeed, -diagonalSpeed));
			break;
		}
		case Direction::NORTH:
		{
			ChangePosition(vector2D(0.0f, -speed));
			break;
		}
		case Direction::NORTHEAST:
		{
			ChangePosition(vector2D(diagonalSpeed, -diagonalSpeed));
			break;
		}
		case Direction::EAST:
		{
			ChangePosition(vector2D(speed, 0.0f));
			break;
		}
		case Direction::SOUTHEAST:
		{
			ChangePosition(vector2D(diagonalSpeed, diagonalSpeed));
			break;
		}
		case Direction::SOUTH:
		{
			ChangePosition(vector2D(0.0f, speed));
			break;
		}
		case Direction::SOUTHWEST:
		{
			ChangePosition(vector2D(-diagonalSpeed, diagonalSpeed));
			break;
		}
		}
		break;
	}
	}
}
