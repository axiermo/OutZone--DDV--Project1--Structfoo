#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1b.h"
#include "ModuleLevel1f.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleLevel2b.h"
#include "ModulePlayer.h"

ModuleLevel2b::ModuleLevel2b()
{
	FinalScreen = { 0, 0, 240, 5279 };
}

ModuleLevel2b::~ModuleLevel2b()
{}

bool ModuleLevel2b::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	graphics = App->textures->Load("Sprites/Level_2.png");
	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_2.ogg");
	App->audio->PlayMusic(soundtrack);
	App->scene_level1f->Disable();
	App->player->Enable();
	return ret;
}

bool ModuleLevel2b::CleanUp()
{
	LOG("Unloading Final Screen");
	App->player->Disable();
	App->audio->UnloadAudio();
	return true;
}

update_status ModuleLevel2b::Update()
{
	App->render->Blit(graphics, 0, -4959, &FinalScreen);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_level2b, App->scene_title, 2.0F);
	}

	return UPDATE_CONTINUE;
}