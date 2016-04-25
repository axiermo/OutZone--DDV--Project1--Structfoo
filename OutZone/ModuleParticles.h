#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
//#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

//struct Collider;
struct SDL_Texture;
enum COLLIDER_TYPE;

struct Particle
{
	//Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, iPoint speed,/*COLLIDER_TYPE collider_type = COLLIDER_NONE,*/ Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:

	//Particle explosion;
	Particle laser90;
	Particle laser67;
	Particle laser45;
	Particle laser22;
	Particle laser0;
	Particle laser112;
	Particle laser135;
	Particle laser157;
};

#endif // __MODULEPARTICLES_H__