#ifndef __ENERGY_BOX_
#define __ENERGY_BOX_

#include "Enemy.h"

class EnergyBox : public Enemy
{
private:
	Animation rotate;

public:
	EnergyBox(int x, int y);
	void Draw();
};

#endif 