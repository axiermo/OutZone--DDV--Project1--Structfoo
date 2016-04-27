#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;
	SDL_Texture* sprite;
	Particle* change_particle;
public:
	iPoint position;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Shoot() {};
	virtual void Draw() ;
};

#endif // __ENEMY_H__