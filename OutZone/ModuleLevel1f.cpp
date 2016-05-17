#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1f.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include <stdio.h>
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
	App->textures->Unload(graphics);

	return true;
}


update_status ModuleLevel1f::Update()
{

	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);
	
	App->render->Blit(graphics, 0, -3850, &World1,-1.0f);
	App->fonts->Blit(24, 8, 0, App->player->score_text);
	
	App->fonts->Blit(24, 0, 0, "player1");
	App->fonts->Blit(104, 0, 0, "top");
	App->fonts->Blit(160, 0, 0, "player2");
	
	App->fonts->Blit(96, 8, 0, "200000");
	App->fonts->Blit(208, 8, 0, "0");
	return UPDATE_CONTINUE;
}
