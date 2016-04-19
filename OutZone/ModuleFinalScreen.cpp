#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleFinalScreen.h"

ModuleFinalScreen::ModuleFinalScreen()
{
	// ground
	FinalScreen = { 0, 0, 240, 5279 };
}

ModuleFinalScreen::~ModuleFinalScreen()
{}

// Load assets
bool ModuleFinalScreen::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("level2.png");
 	soundtrack = App->audio->Load("Audio .ogg/Chapter 2.ogg");
	
	((Module*)App->player)->Enable();
	return ret;
}

// Load assets
bool ModuleFinalScreen::CleanUp()
{
	LOG("Unloading Final Screen");
	App->audio->CleanUp();
	((Module*)App->player)->Disable();
	return true;
}

// Update: draw background
update_status ModuleFinalScreen::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -4959, &FinalScreen);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->final_screen, App->scene_title, 2.0F);
	}

	return UPDATE_CONTINUE;
}