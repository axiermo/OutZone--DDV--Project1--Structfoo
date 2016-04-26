#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1b.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"

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

bool ModuleTitle::Start()
{

	App->gameover->Disable();
	LOG("Loading first scene");
	
	graphics = App->textures->Load("Sprites/Intro.png");

	return true;
}

bool ModuleTitle::CleanUp()
{
	LOG("Unloading title scene");
	
	return true;
}

update_status ModuleTitle::Update()
{
	App->render->Blit(graphics, 0, 0, &title, 0); 

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_title, App->scene_level1b, 2.0F);
	}

	return UPDATE_CONTINUE;
}
