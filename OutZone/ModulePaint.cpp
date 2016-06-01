
#include "Application.h"
#include "ModulePaint.h"
#include "ModuleLevel1b.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "Enemy.h"
#include "ModuleGameOver.h"

ModulePaint::ModulePaint()
{
	for (uint i = 0; i < MAX_ACTIVE_PAINT; ++i)
		active[i] = nullptr;

	turret_hole.anim.PushBack({ 98, 868, 37, 37 });
	mazurka_hole.anim.PushBack({ 447, 37, 64, 80 });
	truck_mark.anim.PushBack({ 315, 584, 66, 24 });
	truck_hole.anim.PushBack({ 520, 17, 96, 120 });
}

ModulePaint::~ModulePaint()
{}

bool ModulePaint::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Sprites/Enemies/Enemies.png");

	return ret;
}

bool ModulePaint::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PAINT; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModulePaint::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PAINT; ++i)
	{
		Paint* p = active[i];

		if (p == nullptr)
			continue;

		App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), -1.0f);
	}
	return UPDATE_CONTINUE;
}

void ModulePaint::AddPaint(const Paint& particle, int x, int y, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PAINT; ++i)
	{
		if (active[i] == nullptr)
		{
			Paint* p = new Paint(particle);
			p->position.x = x;
			p->position.y = y;

			active[i] = p;
			break;
		}
	}
}

Paint::Paint()
{
	position.SetToZero();
}

Paint::Paint(const Paint& p) : anim(p.anim), position(p.position)
{}




