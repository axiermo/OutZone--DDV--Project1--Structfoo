#ifndef __MODULEEXPLOSION_H__
#define __MODULEEXPLOSION_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleCollision.h"

#define nullrect {0,0,0,0} 

#define MAX_ACTIVE_EXPLOSIONS 20

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Explosion
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;

	bool fx_played = false;

	Explosion();
	Explosion(const Explosion& p);
	~Explosion();
	bool Update();
};

class ModuleExplosion : public Module
{
public:
	ModuleExplosion();
	~ModuleExplosion();

	bool Start();
	update_status Update();
	bool CleanUp();
	void AddExplosion(const Explosion& explosion, int x, int y, iPoint speed, SDL_Rect size_collider, COLLIDER_TYPE collider_type, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Explosion* active[MAX_ACTIVE_EXPLOSIONS];

public:

	// Player
	Explosion Airstrike;
	Explosion Player;
	Explosion Truck_explosion;
};

#endif // __MODULEEXPLOSIONS_H__