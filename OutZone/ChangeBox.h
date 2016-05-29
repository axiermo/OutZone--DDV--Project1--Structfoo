#ifndef __Change_BOX_
#define __Change_BOX_

#include "Enemy.h"

class ChangeBox : public Enemy
{
private:
	Animation rotate;
	uint t = 0;

public:
	ChangeBox(int x, int y);
	void Draw();
};

#endif