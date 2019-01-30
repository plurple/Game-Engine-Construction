#include "Room.h"
#include "AI.h"
#include "Wall.h"
#include "enemy.h"
#include "Collectable.h"
#include "Graphics.h"
#include "KeyItemBase.h"
#include "worldEntity.h"
#include "player.h"
#include "Projectile.h"
#include "Door.h"
#include "Sound.h"


Room::~Room()
{
}


void Room::CreateRoom(std::shared_ptr<Player> player)
{
	ArtificialIntelligence = new AI;

	int wall = rand() % 32;
	for (int i = 0; i < 12; i++)
	{

		std::shared_ptr<Wall> newWall = std::make_shared<Wall>("wall", 8, wall);
		objects.push_back(newWall);
		newWall->ChangePosition(vector2D(40.0f, i*64.0f));
		newWall->SetAlive();

		if (i == 6)
		{
			std::shared_ptr<Door> newDoor = std::make_shared<Door>("door", 3, rand() % 12);
			objects.push_back(newDoor);
			newDoor->ChangePosition(vector2D(40.0f, i*64.0f));
			newDoor->SetAlive();
		}
	}
	for (int i = 0; i < 12; i++)
	{

		std::shared_ptr<Wall> newWall = std::make_shared<Wall>("wall", 8, wall);
		objects.push_back(newWall);
		newWall->ChangePosition(vector2D(744.0f, i*64.0f));
		newWall->SetAlive();
		if (i == 6)
		{
			std::shared_ptr<Door> newDoor = std::make_shared<Door>("door", 3, rand() % 12);
			objects.push_back(newDoor);
			newDoor->ChangePosition(vector2D(744.0f, i*64.0f));
			newDoor->SetAlive();
		}
	}
	for (int i = 0; i < 10; i++)
	{

		std::shared_ptr<Wall> newWall = std::make_shared<Wall>("wall", 8, wall);
		objects.push_back(newWall);
		newWall->ChangePosition(vector2D(i*64.0f + 104, 0.0f));
		newWall->SetAlive();

		if (i == 5)
		{
			std::shared_ptr<Door> newDoor = std::make_shared<Door>("door", 3, rand() % 12);
			objects.push_back(newDoor);
			newDoor->ChangePosition(vector2D(i*64.0f + 104, 0.0f));
			newDoor->SetAlive();
		}
	}
	for (int i = 0; i < 10; i++)
	{

		std::shared_ptr<Wall> newWall = std::make_shared<Wall>("wall", 8, wall);
		objects.push_back(newWall);
		newWall->ChangePosition(vector2D(i*64.0f + 104, 704.0f));
		newWall->SetAlive();
		if (i == 5)
		{
			std::shared_ptr<Door> newDoor = std::make_shared<Door>("door", 3, rand() % 12);
			objects.push_back(newDoor);
			newDoor->ChangePosition(vector2D(i*64.0f + 104, 704.0f));
			newDoor->SetAlive();
		}
	}

	for (int i = 0; i < 8; i++)
	{
		std::shared_ptr<Projectile> newProj = std::make_shared<Projectile>("fireball", 8);
		objects.push_back(newProj);
		projectiles.push_back(newProj);
	}

	for (int i = 0; i < rand() % 11; i++)
	{
		std::shared_ptr<Collectable> newCol = std::make_shared<Collectable>("gold", 8);
		objects.push_back(newCol);
		newCol->Setup(vector2D(104.0f + rand() % 611, 50.0f + rand() % 611), std::vector<int>{0, 8}, 30);
	}

	for (int i = 0; i < rand() % 11; i++)
	{
		std::shared_ptr<Collectable> newCol = std::make_shared<Collectable>("silver", 8);
		objects.push_back(newCol);
		newCol->Setup(vector2D(104.0f + rand() % 611, 50.0f + rand() % 611), std::vector<int>{0, 8}, 15);
	}

	for (int i = 0; i < rand() % 11; i++)
	{
		std::shared_ptr<Collectable> newCol = std::make_shared<Collectable>("copper", 8);
		objects.push_back(newCol);
		newCol->Setup(vector2D(104.0f + rand() % 611, 50.0f + rand() % 611), std::vector<int>{0, 8}, 5);
	}


	std::shared_ptr<KeyItemBase> newKey1 = std::make_shared<KeyItemBase>("key", 7, rand() % 49);
	objects.push_back(newKey1);
	newKey1->Setup(vector2D(104.0f + rand() % 581, 50.0f + rand() % 581), std::vector<int>{0, 0}, 50);

	for (int i = 0; i < rand() % 11; i++)
	{
		std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>("minotaur", 64, 0);
		objects.push_back(newEnemy);
		enemies.push_back(newEnemy);
		int a = rand() % 3;
		newEnemy->Setup(vector2D(104.0f + rand() % 581, 50.0f + rand() % 581), std::vector<int>{0, 8, 16, 24, 32, 34, 40, 48, 56, 64}, (MonsterType)a, 10, -5, 40);
	}


	objects.push_back(player);
}

void Room::Cleanup()
{
	delete ArtificialIntelligence;
	objects.clear();
	projectiles.clear();
	enemies.clear();
}

void Room::Update(World *game, Graphics *Viz, Player *player, std::shared_ptr<Sound> sound)
{
	for (auto p : enemies)
	{
		if (p->GetAlive())//make being hit animation work.
			ArtificialIntelligence->SetState(*p, *player);
	}

	for (auto p : objects)
	{
		p->ChangeMana(0.05f);
		p->Update();
	}

	for (auto p : objects)
	{
		if (!p->GetSingle() && p->GetShooting() && p->GetTag() != Tag::PROJECTILE)
		{
			p->SetShooting();
			for (auto q : projectiles)
			{
				if (!q->GetAlive())
				{
					q->Setup(p->GetFirePoint(), { 0, 0, 8 }, p->GetSide(), (20.0f), p->GetDir());
					p->ChangeMana(-10);
					sound->PlaySound("Data//Sound//Fireball.wav");					

					break;
				}
			}
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		Tag tag = objects[i]->GetTag();
		if ((tag == Tag::PLAYER || tag == Tag::ENEMY || tag == Tag::PROJECTILE) && objects[i]->GetAlive())
		{
			for (size_t j = 0; j < objects.size(); j++)
			{
				Tag entityType = objects[j]->GetTag();
				if (i != j && entityType != Tag::NEUTRAL && entityType != Tag::PROJECTILE && entityType != Tag::BAR && objects[j]->GetAlive())
				{
					objects[i]->Collision(objects[j].get(), *Viz);
				}
			}
		}
	}

}

void Room::Render(World *game, Graphics *Viz)
{
	for (auto p : objects)
	{
		p->Render(*Viz);
	}
}