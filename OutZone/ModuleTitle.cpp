#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleLevel1b.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleLevel1f.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
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
	LOG("Loading first scene");
	App->player->score = 0;
	graphics = App->textures->Load("Sprites/Intro.png");
	App->player->Disable();
	App->collision->Disable();
	App->scene_gameover->Disable();
	App->scene_level1b->Disable();
	App->scene_level1f->Disable();
	App->enemies->Disable();
	App->player->destroyed = false;
	return true;
}

bool ModuleTitle::CleanUp()
{
	LOG("Unloading title scene");
	App->textures->Unload(graphics);

	return true;
}

update_status ModuleTitle::Update()
{
	App->render->Blit(graphics, 0, 0, &title, 0); 
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_title, App->scene_level1b, 1.0f);
	}
	
	return UPDATE_CONTINUE;
}
