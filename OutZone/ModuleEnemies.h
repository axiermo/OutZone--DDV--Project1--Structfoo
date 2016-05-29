#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "GreyTurret.h"
#include "DoorTurret.h"
#include "BigTurret.h"
#include "Soldier1.h"
#include "Door.h"
#include "RedSoldier.h"
#include "BlueSoldier.h"
#include "Mazurka.h"
#include "ModuleAudio.h"

#define MAX_ENEMIES 100

class Enemy;

enum ENEMY_TYPES { NO_TYPE, GREYTURRET, DOORTURRET, BIGTURRET, DOOR, SOLDIER1, REDSOLDIER, TRUCK,TANK, BLUESOLDIER, ENERGYBOX, CHANGEBOX, UPGRADEPOWERUP, ENERGYPOWERUP, CHANGEPOWERUP, MAZURKA, BOMB };

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	int subtype = 0;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y, int subtype);
	SDL_Texture* sprites;
	SDL_Texture* sprites2;

	Mix_Chunk* change_weapon = nullptr;
	Mix_Chunk* pick_bomb = nullptr;
	Mix_Chunk* pick_energy = nullptr;
	Mix_Chunk* small_death = nullptr;
	Mix_Chunk* big_death = nullptr;
	Mix_Chunk* enemy_hit = nullptr;

private:
	void SpawnEnemy(const EnemyInfo& info);
	bool x = true;

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];

};

#endif // __ModuleEnemies_H__