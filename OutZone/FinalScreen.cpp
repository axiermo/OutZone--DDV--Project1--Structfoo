#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "FinalScreen.h"
#include "ModulePlayer.h"

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
	
	
	graphics = App->textures->Load("Sprites/Level_2.png");
	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_2.ogg");
	App->audio->PlayMusic(soundtrack);
	
	App->player->Enable();
	return ret;
}

// Load assets
bool ModuleFinalScreen::CleanUp()
{
	LOG("Unloading Final Screen");
	App->player->Disable();
	App->audio->UnloadAudio();
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