#ifndef _CHANGE_POWER_UP_
#define _CHANGE_POWER_UP_

#include "Enemy.h"

class ChangePowerUp : public Enemy
{
private:

	Animation rotate;


public:

	ChangePowerUp(int x, int y);

	void Draw();
};

#endif 