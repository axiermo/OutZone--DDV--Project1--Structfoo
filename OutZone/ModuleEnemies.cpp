#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "GreyTurret.h"
#include "BigTurret.h"
#include "DoorTurret.h"
#include "Soldier1.h"
#include "RedSoldier.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{}

bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("Sprites/Enemies/Enemies.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Move();
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Draw();
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (enemies[i] != nullptr) enemies[i]->Shoot();
	
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int subtype)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].subtype = subtype;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type){
		case ENEMY_TYPES::GREYTURRET:
			enemies[i] = new GreyTurret(info.x, info.y);
			break;
		case ENEMY_TYPES::BIGTURRET:
			enemies[i] = new BigTurret(info.x, info.y);
			break;
		case ENEMY_TYPES::DOORTURRET:
			enemies[i] = new DoorTurret(info.x, info.y);
			break;
		case ENEMY_TYPES::DOOR:
			enemies[i] = new Door(info.x, info.y);
			break;
		case ENEMY_TYPES::SOLDIER1:
			enemies[i] = new Soldier1(info.x, info.y, info.subtype);
			break;
		case ENEMY_TYPES::REDSOLDIER:
			enemies[i] = new RedSoldier(info.x, info.y, info.subtype);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if ((c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_EXPLOSION) && enemies[i]->lives > 0)
			{
				enemies[i]->lives -= 2;

				if (enemies[i]->lives < 1)
				{
					if (c1->type == COLLIDER_TURRET || c1->type == COLLIDER_ENEMY || c1->type == COLLIDER_BIG_TURRET)
					{
						if (c1->type == COLLIDER_ENEMY) // That kind of enemy instant kill
						{
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
							delete enemies[i];
							enemies[i] = nullptr;
						}
						if (c1->type == COLLIDER_TURRET && enemies[i]->destroyed == false) // This one changes the animation to a hole. Will be killed by the border.
						{
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
							enemies[i]->destroyed = true;
						}

						if (c1->type == COLLIDER_BIG_TURRET && enemies[i]->destroyed == false) // This one changes the animation to a hole. Will be killed by the border.
						{
							App->particles->AddParticle(App->particles->Big_NPC_explosion, enemies[i]->position.x - 25, enemies[i]->position.y - 30, { 0, 0 }, nullrect, COLLIDER_NONE);
							enemies[i]->destroyed = true;
						}

						App->player->score += 390;
					}
				}
			}

			if (c2->type == COLLIDER_BORDER)
			{
				if (c1->type == COLLIDER_TURRET || c1->type == COLLIDER_ENEMY || c1->type == COLLIDER_BIG_TURRET || c1->type == COLLIDER_DEAD)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			break;
		}
	}
}