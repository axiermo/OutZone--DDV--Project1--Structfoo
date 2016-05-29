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

	void SelectAnimation(Directions direction);

	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;

public:

	RedSoldier(int x, int y, int subtype);
	iPoint movementAI();

	uint t = 0;
	uint next_shoot;
	uint last_shoot;

	void Move();
	void Shoot();
	void Draw();
};


#endif // __REDSOLDIER1_H__