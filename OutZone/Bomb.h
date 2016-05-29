#ifndef _BOMB_UP_
#define _BOMB_UP_

#include "Enemy.h"

class Bomb : public Enemy
{
private:
	Animation anim;

public:
	Bomb(int x, int y);
	void Draw();
};

#endif 