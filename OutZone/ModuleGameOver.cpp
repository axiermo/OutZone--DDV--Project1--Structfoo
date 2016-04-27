#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGameOver.h"
#include "ModuleTitle.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleLevel1f.h"
#include "ModuleLevel1b.h"
#include "ModuleCollision.h"

ModuleGameOver::ModuleGameOver()
{
	// ground
	GameOverScreen.x = 0;
	GameOverScreen.y = 0;
	GameOverScreen.w = 240;
	GameOverScreen.h = 320;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	LOG("Loading first scene");

	graphics = App->textures->Load("Sprites/Maps/outzonegg.png");
	soundtrack = App->audio->LoadMusic("Audio/Music/Game_over.ogg");
	App->audio->PlayMusic(soundtrack);

	App->scene_level1b->Disable();
	App->scene_level1f->Disable();
	App->player->Disable();
	App->collision->Disable();
	return true;
}

bool ModuleGameOver::CleanUp()
{
	LOG("Unloading title scene");
	return true;
}

update_status ModuleGameOver::Update()
{
	App->render->Blit(graphics, 0, 0, &GameOverScreen, 0);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_gameover, App->scene_title, 2.0F);
	}

	return UPDATE_CONTINUE;
}
