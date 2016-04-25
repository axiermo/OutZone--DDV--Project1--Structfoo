#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFinalScreen.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ModuleLevel1::ModuleLevel1()
{
	World1 = {0, 0, 240, 3896};
}

ModuleLevel1::~ModuleLevel1()
{}

bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	// Loading music for this specific level and the backgroud
	graphics = App->textures->Load("Sprites/Maps/map1_base.png");

	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_1.ogg");
	App->audio->PlayMusic(soundtrack);
	App->player->Enable(); 

	return ret;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading world1");

	App->player->Disable();
	return true;
}

update_status ModuleLevel1::Update()
{	
	App->render->Blit(graphics, 0, -3576, &World1);
	
	if (App->input->keyboard[SDL_SCANCODE_M] == 1)
	{
		App->fade->FadeToBlack(App->scene_level1, App->final_screen, 2.0F);
	}

	return UPDATE_CONTINUE;
}