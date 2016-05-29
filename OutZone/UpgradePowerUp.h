#ifndef _UPGRADE_POWER_UP_
#define _UPGRADE_POWER_UP_

#include "Enemy.h"

class UpgradePowerUp : public Enemy
{
private:
	Animation rotate;

public:

	UpgradePowerUp(int x, int y);
	void Draw();
};

#endif 