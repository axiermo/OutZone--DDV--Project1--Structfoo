#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleTitle::ModuleTitle()
{
	// ground
	title.x = 0;
	title.y = 0;
	title.w = 240;
	title.h = 320;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleTitle::~ModuleTitle()
{}

// Load assets
bool ModuleTitle::Start()
{
	LOG("Loading first scene");
	
	graphics = App->textures->Load("1181242142241.png");
	
	return true;
}

// UnLoad assets
bool ModuleTitle::CleanUp()
{
	LOG("Unloading title scene");
	
	return true;
}

// Update: draw background
update_status ModuleTitle::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &title, 0); 

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_title, App->scene_level1, 2.0F);
	}

	return UPDATE_CONTINUE;
}
