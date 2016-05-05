#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleCollision.h"

#define nullrect {0,0,0,0} 

#define MAX_ACTIVE_PARTICLES 20

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	Particle* end_particle = nullptr;
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
	void OnCollision(Collider* c1, Collider* c2);
	void AddParticle(const Particle& particle, int x, int y, iPoint speed, SDL_Rect size_collider, COLLIDER_TYPE collider_type, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	// Basic laser

	Particle laserup;
	Particle laser67;
	Particle laserupright;
	Particle laser22;
	Particle laserright;
	Particle laser112;
	Particle laserupleft;
	Particle laser157;
	Particle explosionup;
	Particle explosionupright;
	Particle explosionright;
	Particle explosiondownright;
	Particle explosiondown;
	Particle explosiondownleft;
	Particle explosionleft;
	Particle explosionupleft;	
	Particle end_laser;

	//-----------------------Turret particles--------------------
	Particle start_bullet;
	Particle basic_bullet;
	Particle end_bullet;

	// Turret

	Particle Small_NPC_explosion;
};

#endif // __MODULEPARTICLES_H__