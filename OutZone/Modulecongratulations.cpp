#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCongratulations.h"
#include "ModuleTitle.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleLevel1f.h"
#include "ModuleLevel1b.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "ModuleWindow.h"

ModuleCongratulations::ModuleCongratulations()
{
	// ground
	GameOverScreen.x = 0;
	GameOverScreen.y = 0;
	GameOverScreen.w = 240;
	GameOverScreen.h = 320;
	top.PushBack({ 138, 5, 24, 8 });
	player1.PushBack({ 138, 16, 56, 8 });
	player2.PushBack({ 138, 24, 56, 8 });
	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleCongratulations::~ModuleCongratulations()
{}

bool ModuleCongratulations::Start()
{
	LOG("Loading first scene");

	graphics = App->textures->Load("Sprites/Maps/Congratulations.png");
	graphics2 = App->textures->Load("Sprites/UI/UI.png");
	soundtrack = App->audio->LoadMusic("Audio/Music/Game_over.ogg");
	App->audio->PlayMusic0(soundtrack);

	App->window->checkpoint_1 = false;
	App->window->checkpoint_2 = false;
	App->window->checkpoint_3 = false;
	App->window->checkpoint_4 = false;
	App->window->checkpoint_5 = false;
	App->window->checkpoint_6 = false;
	App->window->checkpoint_7 = false;

	return true;
}

bool ModuleCongratulations::CleanUp()
{
	LOG("Unloading title scene");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	return true;
}

update_status ModuleCongratulations::Update()
{
	App->render->Blit(graphics, 0, 0, &GameOverScreen, 0);

	App->fonts->Blit(24, 8, 0, App->player->score_text);

	App->render->Blit(graphics2, 24, 1, &player1.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 164, 1, &player2.GetCurrentFrame(), -1.0f, false);
	App->fonts->Blit(212, 8, 0, "0");
	App->render->Blit(graphics2, 104, 1, &top.GetCurrentFrame(), -1.0f, false);

	if (App->player->score < 200000){
		App->fonts->Blit(96, 8, 0, "200000");
	}
	else{
		App->fonts->Blit(96, 8, 0, App->player->score_text);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_congratulations, App->scene_title, 2.0F);
	}

	return UPDATE_CONTINUE;
}
