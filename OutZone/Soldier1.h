#ifndef __ENEMY_SOLDIER1_H__
#define __ENEMY_SOLDIER1_H__

#include "Enemy.h"
#include"p2Point.h"
#include"Path.h"

class Soldier1 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint original_pos;
	Animation walk;
	Path path;
	Directions direction;

public:

	Soldier1(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;

	void Move();
	void Shoot();
	void Draw();
};

#endif // __ENEMY_SOLDIER1_H__