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
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
ModuleGameOver::ModuleGameOver()
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

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	LOG("Loading first scene");
	App->particles->Disable();
	graphics = App->textures->Load("Sprites/Maps/outzonegg.png");
	graphics2 = App->textures->Load("Sprites/UI/UI.png");
	soundtrack = App->audio->LoadMusic("Audio/Music/Game_over.ogg");
	App->audio->PlayMusic0(soundtrack);
	return true;
}

bool ModuleGameOver::CleanUp()
{
	LOG("Unloading title scene");
	App->textures->Unload(graphics);
	
	return true;
}

update_status ModuleGameOver::Update()
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
		App->fade->FadeToBlack(App->scene_gameover, App->scene_title, 2.0F);
	}

	return UPDATE_CONTINUE;
}
