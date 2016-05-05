#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Basic laser -------------------------------------------

	laserup.anim.PushBack({ 43, 100, 4, 16 });
	laserup.life = 1000;
	laserup.end_particle = &end_laser;
	explosionup.anim.PushBack({ 39, 46, 14, 16 });
	explosionup.life = 10;
	explosiondown.anim.PushBack({ 38, 69, 16, 16 });
	explosiondown.life = 10;

	laserupright.anim.PushBack({ 72, 100, 14, 15 });
	laserupright.life = 1000;
	laserupright.end_particle = &end_laser;
	explosionupright.anim.PushBack({ 75, 48, 16, 14 });
	explosionupright.life = 10;
	explosiondownleft.anim.PushBack({ 77, 71, 14, 13 });
	explosiondownleft.life = 10;

	laserright.anim.PushBack({ 115, 112, 18, 8 });
	laserright.life = 1000;
	laserright.end_particle = &end_laser;
	explosionright.anim.PushBack({ 113, 48, 16, 14 });
	explosionright.life = 10;
	explosionleft.anim.PushBack({ 113, 70, 16, 15 });
	explosionleft.life = 10;

	laserupleft.anim.PushBack({ 158, 100, 14, 15 });
	laserupleft.life = 1000;
	laserupleft.end_particle = &end_laser;
	explosiondownright.anim.PushBack({ 152, 48, 15, 14 });
	explosiondownright.life = 10;
	explosionupleft.anim.PushBack({ 154, 69, 14, 16 });
	explosionupleft.life = 10;

	end_laser.anim.PushBack({ 82, 132, 18, 18 });
	end_laser.anim.PushBack({ 104, 132, 18, 18 });
	end_laser.anim.PushBack({ 124, 132, 18, 18 });
	end_laser.anim.PushBack({ 148, 132, 18, 18 });
	end_laser.anim.speed = 0.4;
	end_laser.life = 100;

	//Turret Particles --------------------------------

	start_bullet.anim.PushBack({ 5, 7, 18, 18 });
	start_bullet.life = 10;

	basic_bullet.anim.PushBack({ 65, 305, 6, 6 });
	basic_bullet.anim.PushBack({ 73, 305, 6, 6 });
	basic_bullet.end_particle = &end_bullet;
	basic_bullet.life = 2000;

	end_bullet.anim.PushBack({ 52, 11, 10, 10 });
	end_bullet.anim.PushBack({ 63, 11, 10, 10 });
	end_bullet.anim.PushBack({ 75, 11, 10, 10 });
	basic_bullet.end_particle = &end_bullet;
	end_bullet.anim.speed = 0.4f;
	end_bullet.life = 10;

	/* Laser sweep
	laser67.anim.PushBack({ 56, 100, 10, 16 });
	laser67.life = 1000;
	laser67.end_particle = &end_laser;
	laser22.anim.PushBack({ 92, 112, 15, 14 });
	laser22.life = 1000;
	laser22.end_particle = &end_laser;
	laser112.anim.PushBack({ 127, 100, 15, 14 });
	laser112.life = 1000;
	laser112.end_particle = &end_laser;
	laser157.anim.PushBack({ 179, 100, 10, 16 });
	laser157.life = 1000;
	laser157.end_particle = &end_laser;
	*/

	Small_NPC_explosion.anim.PushBack({ 31, 178, 39, 38 });
	Small_NPC_explosion.anim.PushBack({ 86, 176, 44, 43 });
	Small_NPC_explosion.anim.PushBack({ 146, 178, 39, 37 });
	Small_NPC_explosion.anim.PushBack({ 36, 243, 30, 36 });
	Small_NPC_explosion.anim.PushBack({ 96, 244, 24, 29 });
	Small_NPC_explosion.anim.PushBack({ 141, 246, 16, 19 });
	Small_NPC_explosion.anim.PushBack({ 177, 252, 9, 11 });
	Small_NPC_explosion.anim.speed = 0.4;
	Small_NPC_explosion.life = 100;

}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("Sprites/Lasers/Basic.png");	
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
	
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, iPoint speed, SDL_Rect size_collider, COLLIDER_TYPE collider_type, Uint32 delay)
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
			
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(size_collider, collider_type, this);

			active[i] = p;
			break;
		}
	}
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed), end_particle(p.end_particle),
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

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1 && active[i]->end_particle != nullptr&& c2->type == COLLIDER_WALL && c1->type == COLLIDER_PLAYER_SHOT)
		{
			AddParticle(*active[i]->end_particle, active[i]->position.x - 5, active[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
			active[i]->collider->to_delete = true;
			delete active[i];
			active[i] = nullptr;
			break;
		}
		if (active[i] != nullptr && active[i]->collider == c1 && active[i]->end_particle != nullptr&&c2->type == COLLIDER_PLAYER &&c1->type == COLLIDER_ENEMY_SHOT)
		{
			AddParticle(*active[i]->end_particle, active[i]->position.x - 5, active[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
			active[i]->collider->to_delete = true;
			delete active[i];
			active[i] = nullptr;
			App->player->destroyed = true;

			break;
		}
	}
}
