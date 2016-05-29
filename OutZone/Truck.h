#ifndef __ENEMY_TRUCK_H__
#define  __ENEMY_TRUCK_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Truck : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	iPoint original_pos;
	Animation up;
	Animation down;
	Animation stop;
	Path path;
	Directions direction;

	void SelectAnimation(Directions direction);

	uint t = 0;
	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;

public:


	Truck(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;

	void Move();
	void Draw();
};

#endif //  __ENEMY_TRUCK_H__