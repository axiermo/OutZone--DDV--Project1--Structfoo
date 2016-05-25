#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "GreyTurret.h"
#include "DoorTurret.h"
#include "BigTurret.h"
#include "Soldier1.h"
#include "Door.h"

#define MAX_ENEMIES 100

class Enemy;

enum ENEMY_TYPES { NO_TYPE, GREYTURRET, DOORTURRET, BIGTURRET, DOOR, SOLDIER1 };

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

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];

};

#endif // __ModuleEnemies_H__