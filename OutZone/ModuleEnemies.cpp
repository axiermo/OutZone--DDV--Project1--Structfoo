#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleExplosion.h"
#include "ModulePaint.h"
#include "Enemy.h"
#include "GreyTurret.h"
#include "BigTurret.h"
#include "DoorTurret.h"
#include "Soldier1.h"
#include "RedSoldier.h"
#include "ChangeBox.h"
#include "UpgradePowerUp.h"
#include "EnergyBox.h"
#include "EnergyPowerUp.h"
#include "ChangePowerUp.h"
#include "Truck.h"
#include "BlueSoldier.h"
#include "Mazurka.h"
#include "Tank.h"
#include "Bomb.h"

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
	sprites2 = App->textures->Load("Sprites/Enemies/Enemies2.png");

	pick_energy = App->audio->LoadFX("Audio/FX/Pick_energy.wav");
	pick_bomb = App->audio->LoadFX("Audio/FX/Pick_bomb.wav");
	change_weapon = App->audio->LoadFX("Audio/FX/Change_weapon.wav");
	small_death = App->audio->LoadFX("Audio/FX/Small_enemy_death.wav");
	big_death = App->audio->LoadFX("Audio/FX/Big_enemy_death.wav");
	enemy_hit = App->audio->LoadFX("Audio/FX/Enemy_hit.wav");

	x = true;

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
	App->textures->Unload(sprites2);

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
		case ENEMY_TYPES::TRUCK:
			enemies[i] = new Truck(info.x, info.y, info.subtype);
			break;
		case ENEMY_TYPES::BLUESOLDIER:
			enemies[i] = new BlueSoldier(info.x, info.y, info.subtype);
			break;
		case ENEMY_TYPES::ENERGYBOX:
			enemies[i] = new EnergyBox(info.x, info.y);
			break;
		case ENEMY_TYPES::CHANGEBOX:
			enemies[i] = new ChangeBox(info.x, info.y);
			break;
		case ENEMY_TYPES::UPGRADEPOWERUP:
			enemies[i] = new UpgradePowerUp(info.x, info.y);
			break;
		case ENEMY_TYPES::ENERGYPOWERUP:
			enemies[i] = new EnergyPowerUp(info.x, info.y);
			break;
		case ENEMY_TYPES::CHANGEPOWERUP:
			enemies[i] = new ChangePowerUp(info.x, info.y);
			break;
		case ENEMY_TYPES::MAZURKA:
			enemies[i] = new Mazurka(info.x, info.y, info.subtype);
			break;
		case ENEMY_TYPES::TANK:
			enemies[i] = new Tank(info.x, info.y, info.subtype);
			break;
		case ENEMY_TYPES::BOMB:
			enemies[i] = new Bomb(info.x, info.y);
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
			if ((c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_EXPLOSION || c2->type == COLLIDER_GOD) && enemies[i]->lives > 0)
			{
				
				if (c2->type == COLLIDER_EXPLOSION)
				{
					enemies[i]->lives -= 1;
				}
				else
					enemies[i]->lives -= App->player->damage;

				
				enemies[i]->hit = true;
				App->audio->PlayFX(enemy_hit);

				if (enemies[i]->lives < 1)
				{
					if (c1->type == COLLIDER_DOOR || c1->type == COLLIDER_BOX || c1->type == COLLIDER_TURRET || c1->type == COLLIDER_MAZURKA || c1->type == COLLIDER_ENEMY || c1->type == COLLIDER_BIG_TURRET || c1->type == COLLIDER_RED_SOLDIER || c1->type == COLLIDER_TRUCK)
					{
						if (c1->type == COLLIDER_ENEMY) // That kind of enemy instant kill
						{
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
							App->audio->PlayFX(small_death);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->score += 390;
						}
						if (c1->type == COLLIDER_BOX) // That kind of enemy instant kill
						{
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
							App->audio->PlayFX(small_death);
							delete enemies[i];
							enemies[i] = nullptr;
						}
						if (c1->type == COLLIDER_RED_SOLDIER) // That kind of enemy instant kill
						{
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);

							if (x == true)
							{
								if (App->player->laser < 4) App->enemies->AddEnemy(ENEMY_TYPES::UPGRADEPOWERUP, enemies[i]->position.x + 2, enemies[i]->position.y + 10, 0);
								else App->enemies->AddEnemy(ENEMY_TYPES::BOMB, enemies[i]->position.x + 2, enemies[i]->position.y + 10, 0);
								x = false;
							}
							else
							{
								App->enemies->AddEnemy(ENEMY_TYPES::BOMB, enemies[i]->position.x + 2, enemies[i]->position.y + 10, 0);
								x = true;
							}

							App->audio->PlayFX(small_death);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->score += 490;
						}
						if (c1->type == COLLIDER_TURRET) // Instant kill.
						{
							App->audio->PlayFX(small_death);
							App->particles->AddParticle(App->particles->Small_NPC_explosion, enemies[i]->position.x, enemies[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
							App->paint->AddPaint(App->paint->turret_hole, enemies[i]->position.x - 1, enemies[i]->position.y + 12);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->score += 410;
						}

						if (c1->type == COLLIDER_BIG_TURRET && enemies[i]->destroyed == false) // This one changes the animation to a hole. Will be killed by the border.
						{
							App->audio->PlayFX(big_death);
							App->particles->AddParticle(App->particles->Big_NPC_explosion, enemies[i]->position.x - 25, enemies[i]->position.y - 30, { 0, 0 }, nullrect, COLLIDER_NONE);
							enemies[i]->destroyed = true;
							App->player->score += 810;
						}
						if (c1->type == COLLIDER_MAZURKA) // Instant kill.
						{
							App->audio->PlayFX(big_death);
							App->particles->AddParticle(App->particles->Big_NPC_explosion, enemies[i]->position.x - 25, enemies[i]->position.y - 30, { 0, 0 }, nullrect, COLLIDER_NONE);
							App->paint->AddPaint(App->paint->mazurka_hole, enemies[i]->position.x, enemies[i]->position.y);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->mazurkaskilled++;
							App->player->score += 13060;
						}
						if (c1->type == COLLIDER_TRUCK) // Instant kill.
						{
							App->audio->PlayFX(big_death);
							App->explosion->AddExplosion(App->explosion->Truck_explosion, enemies[i]->position.x - 20, enemies[i]->position.y - 10, { 0, 0 }, { 0, 0, 100, 150 }, COLLIDER_EXPLOSION);
							App->paint->AddPaint(App->paint->truck_hole, enemies[i]->position.x - 10, enemies[i]->position.y);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->score += 1770;
						}
						if (c1->type == COLLIDER_DOOR) // Instant kill.
						{
							App->audio->PlayFX(big_death);
							App->explosion->AddExplosion(App->explosion->Truck_explosion, enemies[i]->position.x - 20, enemies[i]->position.y - 10, { 0, 0 }, { 0, 0, 100, 150 }, COLLIDER_EXPLOSION);
							delete enemies[i];
							enemies[i] = nullptr;
							App->player->score += 1530;
						}
					}
				}
			}
			if (c2->type == COLLIDER_BORDER)
			{
				if (c1->type == COLLIDER_TURRET || c1->type == COLLIDER_ENEMY || c1->type == COLLIDER_RED_SOLDIER|| c1->type == COLLIDER_BIG_TURRET || c1->type == COLLIDER_DEAD || c1->type == COLLIDER_TRUCK || c1->type == COLLIDER_DOOR)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_GOD)
			{
				if (c1->type == COLLIDER_CHANGE)
				{
					App->audio->PlayFX(change_weapon);
					App->player->curr_animation = &App->player->up2;
					App->player->weapon = !App->player->weapon;
					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (c1->type == COLLIDER_ENERGY)
				{
					App->audio->PlayFX(pick_energy);

					if (App->player->energy < 20) App->player->energy += 16;
					else App->player->energy = 36;

					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (c1->type == COLLIDER_UPGRADE)
				{
					App->audio->PlayFX(change_weapon);

					if (App->player->laser < 3) App->player->laser++;
					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (c1->type == COLLIDER_BOMB)
				{
					App->audio->PlayFX(pick_bomb);

					App->player->bombs++;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			break;
		}
	}
}