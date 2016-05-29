#ifndef _UPGRADE_POWER_UP_
#define _UPGRADE_POWER_UP_

#include "Enemy.h"

class UpgradePowerUp : public Enemy
{
private:

	Animation rotate;
	uint t = 0;
public:

	UpgradePowerUp(int x, int y);
	void Draw();
};

#endif 