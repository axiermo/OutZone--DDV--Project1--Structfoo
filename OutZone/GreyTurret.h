#ifndef __GREYTURRET_H__
#define __GREYTURRET_H__

#include "Enemy.h"

class GreyTurret : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	Animation rotate;
	Directions direction;

public:
	uint next_shoot;
	uint last_shoot;
	GreyTurret(int x, int y);
	void Move();
	void Shoot();
	void Draw();
};

#endif // __ENEMY_TURRET_H__