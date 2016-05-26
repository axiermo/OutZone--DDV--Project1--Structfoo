#ifndef __ENEMY_BLUESOLDIER_H__
#define __ENEMY_BLUESOLDIER_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class BlueSoldier : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	iPoint original_pos;
	Animation up;
	Animation upright;
	Animation right;
	Animation downright;
	Animation down;
	Animation downleft;
	Animation left;
	Animation upleft;
	Animation walk;
	Path path;
	Directions direction;

	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;

public:

	void SelectAnimation(Directions direction);

	BlueSoldier(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;

	void Move();
	void Shoot();
	void Draw();
};

#endif // __ENEMY_BLUESOLDIER_H__