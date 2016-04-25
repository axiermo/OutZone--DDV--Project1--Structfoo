#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Animation.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	
	//Basic laser
	graphics = App->textures->Load("Sprites/Lasers/Basic.png");
	laser90.anim.PushBack({ 43, 100, 6, 18 });
	laser90.life = 1000;
	laser67.anim.PushBack({ 56, 100, 10, 16 });
	laser67.life = 1000;
	laser45.anim.PushBack({ 72, 100, 14, 15 });
	laser45.life = 1000;
	laser22.anim.PushBack({ 92, 112, 15, 14 });
	laser22.life = 1000;
	laser0.anim.PushBack({ 115, 112, 18, 8 });
	laser0.life = 1000;
	laser112.anim.PushBack({ 127, 100, 15, 14 });
	laser112.life = 1000;
	laser135.anim.PushBack({ 158, 100, 14, 15 });
	laser135.life = 1000;
	laser157.anim.PushBack({ 179, 100, 10, 16 });
	laser157.life = 1000;

	return true;
}

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
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, iPoint speed, /*COLLIDER_TYPE collider_type,*/ Uint32 delay)
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
			/*
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			*/
			active[i] = p;
			break;
		}
	}
}

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



/* TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
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
*/

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
	/*if (collider != nullptr)
		App->collision->EraseCollider(collider);*/
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

	/*if (collider != nullptr)
		collider->SetPos(position.x, position.y);*/

	return ret;
}

