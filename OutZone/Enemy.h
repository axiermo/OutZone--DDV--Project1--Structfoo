#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;
	Path* path;

public:
	iPoint position;
	int lives = 2;
	int subtype;
	bool destroyed = false;
	bool appeared = false;

public:
	Enemy(int x, int y, int subtype);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw();
};

#endif // __ENEMY_H__