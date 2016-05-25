#ifndef __DOOR_TURRET_H__
#define __DOOR_TURRET_H__

#include "Enemy.h"

class DoorTurret : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	Animation anim;
	Animation dead;
	Directions direction;

public:
	uint next_shoot;
	uint last_shoot;
	DoorTurret(int x, int y);
	void Move() {};
	void Shoot();
	void Draw();
};
#endif // !__DOOR_TURRET_H__