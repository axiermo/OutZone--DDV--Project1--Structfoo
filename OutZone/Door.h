#ifndef __DOOR_H__
#define __DOOR_H__

#include "Enemy.h"

class Door : public Enemy{
private:
	float wave = -1.0f;
	bool going_up = true;
	Animation anim;
	Directions direction;

public:
	Door(int x, int y);
	void Move(){};
	void Shoot(){};
	void Draw();
};

#endif // __DOOR_H__