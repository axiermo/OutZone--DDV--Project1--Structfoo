#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFinalScreen.h"

ModuleLevel1::ModuleLevel1()
{
	World1 = {0, 0, 240, 3896};
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("level1.png");
	soundtrack = App->audio->Load("Audio .ogg/Chapter 1.ogg");

	
	((Module*)App->player)->Enable(); 
	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading world1");

	((Module*)App->player)->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -3576, &World1);
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_level1, App->final_screen, 2.0F);
	}
	return UPDATE_CONTINUE;
}