#ifndef __REDSOLDIER_H__
#define __REDSOLDIER_H__

#include "Enemy.h"
#include"p2Point.h"
#include"Path.h"

class RedSoldier : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint original_pos;
	Animation walk;
	Path path;
	Directions direction;

public:

	RedSoldier(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;

	void Move();
	void Shoot();
	void Draw();
};

#endif // __REDSOLDIER1_H__