#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	//Basic laser
	graphics = App->textures->Load("Sprites/Lasers/Basic.png");
	laserup.anim.PushBack({ 43, 100, 4, 16 });
	laserup.life = 1000;
	laser67.anim.PushBack({ 56, 100, 10, 16 });
	laser67.life = 1000;
	laserupright.anim.PushBack({ 72, 100, 14, 15 });
	laserupright.life = 1000;
	laser22.anim.PushBack({ 92, 112, 15, 14 });
	laser22.life = 1000;
	laserright.anim.PushBack({ 115, 112, 18, 8 });
	laserright.life = 1000;
	laser112.anim.PushBack({ 127, 100, 15, 14 });
	laser112.life = 1000;
	laserupleft.anim.PushBack({ 158, 100, 14, 15 });
	laserupleft.life = 1000;
	laser157.anim.PushBack({ 179, 100, 10, 16 });
	laser157.life = 1000;

	explosionup.anim.PushBack({ 39, 46, 14, 16 });
	explosionup.life = 10;
	explosiondown.anim.PushBack({ 38, 69, 16 , 16 });
	explosiondown.life = 10;
	
	
	explosionupright.anim.PushBack({ 75, 48, 16, 14 });
	explosionupright.life = 10;

	explosionright.anim.PushBack({ 113, 48, 16, 14 });
	explosionright.life = 10;

	explosiondownright.anim.PushBack({ 152, 48, 15, 14 });
	explosiondownright.life = 10;

	explosiondownleft.anim.PushBack({ 77, 71, 14, 13 });
	explosiondownleft.life = 10;

	explosionleft.anim.PushBack({ 113, 70, 16, 15 });
	explosionleft.life = 10;

	explosionupleft.anim.PushBack({ 154, 69, 14, 16 });
	explosionupleft.life = 10;
	return true;
	
	}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}

		
	}
	return UPDATE_CONTINUE;
}
	
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, iPoint speed, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->speed = speed;
			
				
			active[i] = p;
			
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}

}

// -------------------------------------------------------------
// -------------------------------------------------------------
	
Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}


Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
	if (anim.Finished())
		ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
