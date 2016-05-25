#ifndef __BIG_TURRET_H__
#define __BIG_TURRET_H__

#include "Enemy.h"

class BigTurret : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	bool left = true;

	Animation anim;
	Animation dead;
	Directions direction;

public:
	uint next_shoot;
	uint last_shoot;
	BigTurret(int x, int y);
	void Move() {};
	void Shoot();
	void Draw();
};
#endif // !__BIG_TURRET_H__