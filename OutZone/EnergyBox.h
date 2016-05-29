#ifndef __ENERGY_BOX_
#define __ENERGY_BOX_

#include "Enemy.h"

class EnergyBox : public Enemy
{
private:
	Animation rotate;
	uint t = 0;
public:
	EnergyBox(int x, int y);
	void Draw();
};

#endif 