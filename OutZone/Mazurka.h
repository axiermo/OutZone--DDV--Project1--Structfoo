#ifndef __MAZURKA_H__
#define __MAZURKA_H__
#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
class Mazurka : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint original_pos;
	Animation dead;
	Animation mazurka;
	Animation stopmazurka;
	Animation hit2;
	Path path;
	Directions direction;
public:
	Mazurka(int x, int y, int subtype);
	uint next_shoot;
	uint last_shoot;
	uint t = 0;
	void Move();
	void Shoot();
	void Draw();
};
#endif // __MAZURKA_H__