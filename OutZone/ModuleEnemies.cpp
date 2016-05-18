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
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
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
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
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

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
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
			enemies[i] = new Soldier1(info.x, info.y);
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
			if ((c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_BORDER) && enemies[i]->lives > 0)
			{
				enemies[i]->lives -= 2;

				if (enemies[i]->lives < 1)
				{
					if (c1->type == COLLIDER_TURRET) App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x - 7, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
					// All ifs from the differents enemies-explosions we have.
					delete enemies[i];
					enemies[i] = nullptr;
					if (c2->type == COLLIDER_PLAYER_SHOT) App->player->score += 390;
				}
			}
			break;
		}
	}
}