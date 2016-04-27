#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1f.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ModuleLevel1f::ModuleLevel1f()
{
	World1 = { 0, 0, 256, 4180 };
}

ModuleLevel1f::~ModuleLevel1f()
{}

bool ModuleLevel1f::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Sprites/Maps/map1_foreground.png");

	return ret;
}

bool ModuleLevel1f::CleanUp()
{
	LOG("Unloading world1");
	App->player->Disable();
	App->collision->Disable();
	App->textures->Unload(graphics);
	return true;
}


update_status ModuleLevel1f::Update()
{
	App->render->Blit(graphics, 0, -3850, &World1);

	return UPDATE_CONTINUE;
}
