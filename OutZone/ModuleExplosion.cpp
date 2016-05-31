#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleExplosion.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"

ModuleExplosion::ModuleExplosion()
{
	for (uint i = 0; i < MAX_ACTIVE_EXPLOSIONS; ++i)
		active[i] = nullptr;

	//------------------------ Airstrike ---------------------------

	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 0), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 1), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 2), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 3), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 4), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 5), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 6), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 7), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 8), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 9), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 10), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 11), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 12), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 13), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 14), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.PushBack({ 0 + (SCREEN_WIDTH * 15), 340, SCREEN_WIDTH, SCREEN_HEIGHT });
	Airstrike.anim.speed = 0.9f;
	Airstrike.life = 280;
	Airstrike.anim.loop = false;

	Player.anim.PushBack({ 241, 0, 115, 110 });
	Player.anim.PushBack({ 361, 0, 115, 110 });
	Player.anim.PushBack({ 479, 0, 115, 110 });
	Player.anim.PushBack({ 596, 0, 115, 110 });
	Player.anim.PushBack({ 237, 112, 117, 114 });
	Player.anim.PushBack({ 359, 113, 113, 113 });
	Player.anim.PushBack({ 476, 113, 113, 113 });
	Player.anim.PushBack({ 593, 113, 114, 112 });
	Player.anim.PushBack({ 710, 113, 113, 113 });
	Player.anim.speed = 0.2f;
	Player.life = 700;
	Player.anim.loop = false;

	Truck_explosion.anim.PushBack({ 276, 14, 157, 130 });
	Truck_explosion.anim.PushBack({ 417, 14, 157, 130 });
	Truck_explosion.anim.PushBack({ 560, 14, 157, 130 });
	Truck_explosion.anim.PushBack({ 276, 143, 157, 130 });
	Truck_explosion.anim.PushBack({ 417, 143, 157, 130 });
	Truck_explosion.anim.PushBack({ 560, 143, 157, 130 });
	Truck_explosion.anim.PushBack({ 702, 143, 157, 130 });
	Truck_explosion.anim.speed = 0.5;
	Truck_explosion.life = 150;
	Truck_explosion.anim.loop = false;
}

ModuleExplosion::~ModuleExplosion()
{}

bool ModuleExplosion::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("Sprites/Explosions/All.png");
	return true;
}

bool ModuleExplosion::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_EXPLOSIONS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleExplosion::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_EXPLOSIONS; ++i)
	{
		Explosion* e = active[i];

		if (e == nullptr)
			continue;

		if (e->Update() == false)
		{
			delete e;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= e->born)
		{
			App->render->Blit(graphics, e->position.x, e->position.y, &(e->anim.GetCurrentFrame()), -1.0f);
			if (e->fx_played == false)
			{
				e->fx_played = true;
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleExplosion::AddExplosion(const Explosion& explosion, int x, int y, iPoint speed, SDL_Rect size_collider, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_EXPLOSIONS; ++i)
	{
		if (active[i] == nullptr)
		{
			Explosion* e = new Explosion(explosion);
			e->born = SDL_GetTicks() + delay;
			e->position.x = x;
			e->position.y = y;
			e->speed = speed;

			if (collider_type != COLLIDER_NONE)
				e->collider = App->collision->AddCollider(size_collider, collider_type, this);

			active[i] = e;
			break;
		}
	}
}

Explosion::Explosion()
{
	position.SetToZero();
	speed.SetToZero();
}

Explosion::Explosion(const Explosion& e) :
anim(e.anim), position(e.position), speed(e.speed),
fx(e.fx), born(e.born), life(e.life)
{}


Explosion::~Explosion()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Explosion::Update()
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

