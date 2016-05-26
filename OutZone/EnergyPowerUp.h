#ifndef _ENERGY_POWER_UP_
#define _ENERGY_POWER_UP_

#include "Enemy.h"

class EnergyPowerUp : public Enemy
{
private:

	Animation rotate;


public:


	EnergyPowerUp(int x, int y);

	void Draw();
};

#endif 