#ifndef __ENEMY_TANK_H__
#define __ENEMY_TANK_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Tank : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	iPoint original_pos;
	Animation tankanim;

	uint t = 0;

	Path path;
	Directions direction;

	bool left;

	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;

public:

	void SelectAnimation(Directions direction);

	Tank(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;

	bool done = true;
	void Move();
	void Shoot();
	void Draw();
};

#endif // __ENEMY_TANK_H__