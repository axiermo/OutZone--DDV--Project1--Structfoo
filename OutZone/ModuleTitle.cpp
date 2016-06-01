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
#include "ModuleWindow.h"

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

	credit.PushBack({ 0, 52, 48, 8 });
	pushstart.PushBack({ 0, 10, 120, 40 });

	for (int i = 0; i < 10; i++)
		creditnums.PushBack({ i * 8, 0, 8, 8 });
}

ModuleTitle::~ModuleTitle()
{}

bool ModuleTitle::Start()
{
	App->player->position.x = 100;
	App->player->position.y = 220;

	LOG("Loading first scene");
	App->player->score = 0;
	App->player->energy = 36;
	App->player->lives = 3;
	stop = false;
	t = 0;

	graphics = App->textures->Load("Sprites/Maps/Intro.png");
	graphics2 = App->textures->Load("Sprites/UI/UIIntro.png");
	insertcoin = App->audio->LoadFX("Audio/FX/Coin.wav");

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
	App->render->Blit(graphics2, 88, 296, &credit.GetCurrentFrame(), 1.0f, false);

	// Drawing coins
 	creditnums.setframe(coins);
	App->render->Blit(graphics2, 88 + 56, 296, &creditnums.GetActualFrame(), 1.0f, false);

	// Drawing press start
	if (coins >= 1)
		App->render->Blit(graphics2, 64, 169, &pushstart.GetCurrentFrame(), 1.0f, false);

	// Adding coins
	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_UP && coins < 9)
	{
		if (coins == 0)
		{
			App->window->checkpoint_1 = false;
			App->window->checkpoint_2 = false;
			App->window->checkpoint_3 = false;
			App->window->checkpoint_4 = false;
			App->window->checkpoint_5 = false;
			App->window->checkpoint_6 = false;
			App->window->checkpoint_7 = false;
		}

		App->audio->PlayFX(insertcoin);
		coins++;
	}
		
	// Spending coins
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && coins > 0 && !stop && t > 70)
	{
		if (App->window->checkpoint_7 == true)
		{
			App->window->checkpoint_6 = false;
		}
		else if (App->window->checkpoint_6 == true)
		{
			App->window->checkpoint_6 = false;
		}
		else if (App->window->checkpoint_5 == true)
		{
			App->window->checkpoint_5 = false;
		}
		else if (App->window->checkpoint_4 == true)
		{
			App->window->checkpoint_4 = false;
		}
		else if (App->window->checkpoint_3 == true)
		{
			App->window->checkpoint_3 = false;
		}
		else if (App->window->checkpoint_2 == true)
		{
			App->window->checkpoint_2 = false;
		}
		else if (App->window->checkpoint_1 == true)
		{
			App->window->checkpoint_1 = false;
		}
		
		coins -= 1;
		stop = true;
	}

	if (stop == true)
		App->fade->FadeToBlack(App->scene_title, App->scene_level1b, 1.0f);

	t++;
	return UPDATE_CONTINUE;
}
