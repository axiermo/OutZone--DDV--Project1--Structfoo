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

	// 1st
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

	// 2nd
	laserup2.anim.PushBack({ 44, 25, 10, 16 });
	laserup2.life = 1000;
	laserup2.end_particle = &end_laser;

	laserupright2.anim.PushBack({ 73, 25, 16, 16 });
	laserupright2.life = 1000;
	laserupright2.end_particle = &end_laser;

	laserright2.anim.PushBack({ 111, 28, 16, 10 });
	laserright2.life = 1000;
	laserright2.end_particle = &end_laser;

	laserupleft2.anim.PushBack({ 149, 25, 16, 16 });
	laserupleft2.life = 1000;
	laserupleft2.end_particle = &end_laser;

	// 3rd
	laser3.anim.PushBack({ 9, 53, 26, 26 });
	laser3.life = 1000;
	laser3.end_particle = &end_laser;

	// End
	end_laser.anim.PushBack({ 80, 132, 18, 18 });
	end_laser.anim.PushBack({ 104, 132, 18, 18 });
	end_laser.anim.PushBack({ 124, 132, 18, 18 });
	end_laser.anim.PushBack({ 148, 132, 18, 18 });
	end_laser.anim.speed = 0.4;
	end_laser.life = 100;

	// Laser sweep 2
	laser67_2.anim.PushBack({ 58, 25, 14, 17 });
	laser67_2.life = 1000;
	laser67_2.end_particle = &end_laser;
	laser22_2.anim.PushBack({ 92, 25, 17, 17 });
	laser22_2.life = 1000;
	laser22_2.end_particle = &end_laser;
	laser157_2.anim.PushBack({ 130, 25, 15, 18 });
	laser157_2.life = 1000;
	laser157_2.end_particle = &end_laser;
	laser112_2.anim.PushBack({ 169, 25, 15, 18 });
	laser112_2.life = 1000;
	laser112_2.end_particle = &end_laser;

	// Laser sweep 1
	laser67.anim.PushBack({ 52, 102, 11, 17 });
	laser67.life = 1000;
	laser67.end_particle = &end_laser;
	laser22.anim.PushBack({ 92, 107, 17, 12 });
	laser22.life = 1000;
	laser22.end_particle = &end_laser;
	laser112.anim.PushBack({ 179, 100, 11, 16 });
	laser112.life = 1000;
	laser112.end_particle = &end_laser;
	laser157.anim.PushBack({ 137, 107, 16, 10 });
	laser157.life = 1000;
	laser157.end_particle = &end_laser;


	// Triple laser --------------------------------------------------------------------

	// 1st
	triple1l.anim.PushBack({ 214, 136, 9, 11 });
	triple1l.life = 1000;
	triple1l.end_particle = &end_triple;
	triple1c.anim.PushBack({ 228, 136, 6, 13 });
	triple1c.life = 1000;
	triple1c.end_particle = &end_triple;
	triple1r.anim.PushBack({ 238, 136, 9, 11 });
	triple1r.life = 1000;
	triple1r.end_particle = &end_triple;

	// 2nd
	triple2l.anim.PushBack({ 210, 112, 11, 17 });
	triple2l.life = 1000;
	triple2l.end_particle = &end_triple;
	triple2c.anim.PushBack({ 226, 111, 10, 17 });
	triple2c.life = 1000;
	triple2c.end_particle = &end_triple;
	triple2r.anim.PushBack({ 242, 112, 11, 17 });
	triple2r.life = 1000;
	triple2r.end_particle = &end_triple;

	// 3rd
	triple3l.anim.PushBack({ 203, 84, 16, 21 });
	triple3l.life = 1000;
	triple3l.end_particle = &end_triple;
	triple3c.anim.PushBack({ 224, 84, 14, 22 });
	triple3c.life = 1000;
	triple3c.end_particle = &end_triple;
	triple3r.anim.PushBack({ 244, 84, 16, 21 });
	triple3r.life = 1000;
	triple3r.end_particle = &end_triple;

	// Exp
	triple_exp.anim.PushBack({ 213, 153, 36, 16 });
	triple_exp.life = 10;

	// End
	end_triple.anim.PushBack({ 223, 60, 16, 21 });
	end_triple.anim.PushBack({ 223, 39, 16, 18 });
	end_triple.anim.PushBack({ 223, 21, 16, 18 });
	end_triple.anim.PushBack({ 223, 0, 16, 18 });
	end_triple.anim.speed = 0.4f;
	end_triple.life = 100;


	//---------------------- BigTurret Particles ---------------------------------------

	Big_Tur_Exp.anim.PushBack({ 221, 244, 31, 30 });
	Big_Tur_Exp.life = 50;

	Big_Tur_Laser.anim.PushBack({ 230, 276, 14, 14 });
	Big_Tur_Laser.anim.PushBack({ 231, 292, 12, 12 });
	Big_Tur_Laser.end_particle = &End_Enemy_Laser;
	Big_Tur_Laser.anim.speed = 0.4f;
	Big_Tur_Laser.life = 4000;

	Big_NPC_explosion.anim.PushBack({ 276, 14, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 417, 14, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 560, 14, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 276, 143, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 417, 143, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 560, 143, 157, 130 });
	Big_NPC_explosion.anim.PushBack({ 702, 143, 157, 130 });
	Big_NPC_explosion.anim.speed = 0.5;
	Big_NPC_explosion.life = 150;

	//------------------------ Door Turret && Grey turret && Soldiers ---------------------------

	Enemy_Exp.anim.PushBack({ 41, 300, 16, 16 });
	Enemy_Exp.life = 50;

	Enemy_Laser.anim.PushBack({ 65, 305, 6, 6 });
	Enemy_Laser.anim.PushBack({ 73, 305, 6, 6 });
	Enemy_Laser.end_particle = &End_Enemy_Laser;
	Enemy_Laser.anim.speed = 0.4f;
	Enemy_Laser.life = 4000;

	End_Enemy_Laser.anim.PushBack({ 88, 304, 8, 8 });
	End_Enemy_Laser.anim.PushBack({ 99, 304, 8, 8 });
	End_Enemy_Laser.anim.PushBack({ 111, 305, 5, 6 });
	End_Enemy_Laser.anim.speed = 0.4f;
	End_Enemy_Laser.life = 100;

	Small_NPC_explosion.anim.PushBack({ 26, 128, 44, 44 });
	Small_NPC_explosion.anim.PushBack({ 31, 178, 40, 40 });
	Small_NPC_explosion.anim.PushBack({ 86, 176, 44, 40 });
	Small_NPC_explosion.anim.PushBack({ 146, 178, 40, 40 });
	Small_NPC_explosion.anim.PushBack({ 31, 241, 40, 40 });
	Small_NPC_explosion.anim.PushBack({ 88, 241, 40, 40 });
	Small_NPC_explosion.anim.PushBack({ 148, 241, 40, 40 });
	Small_NPC_explosion.anim.PushBack({ 205, 188, 40, 40 });
	Small_NPC_explosion.anim.speed = 0.3f;
	Small_NPC_explosion.life = 400;
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("Sprites/Particles/All.png");
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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), -1.0f);
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
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c1->type == COLLIDER_PLAYER_SHOT && c2->type != COLLIDER_BORDER_TOP)
				AddParticle(*active[i]->end_particle, active[i]->position.x - 5, active[i]->position.y - 4, { 0, 0 }, nullrect, COLLIDER_NONE);
			else if (c1->type != COLLIDER_PLAYER_SHOT && c2->type != COLLIDER_BORDER_TOP)
				AddParticle(*active[i]->end_particle, active[i]->position.x, active[i]->position.y, { 0, 0 }, nullrect, COLLIDER_NONE);

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
