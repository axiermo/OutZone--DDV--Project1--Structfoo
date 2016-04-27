#ifndef __GREYTURRET_H__
#define __GREYTURRET_H__

#include "Enemy.h"

class GreyTurret : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint original_point;
	Animation rotate;

	Animation bot;
	Animation bot_left;
	Animation left;
	Animation top_left;
	Animation top;
	Animation top_right;
	Animation right;
	Animation bot_right;

public:

	GreyTurret(int x, int y);
	void Rotate(int player_x, int player_y);
};

#endif // __ENEMY_TURRET_H__