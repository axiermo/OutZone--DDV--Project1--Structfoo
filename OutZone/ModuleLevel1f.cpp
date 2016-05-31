#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1f.h"
#include "ModuleLevel1b.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "Enemy.h"
#include "ModuleGameOver.h"
#include <stdio.h>

ModuleLevel1f::ModuleLevel1f()
{
	World1 = { 0, 0, 256, 4180 };
	insertcoin.PushBack({ 10, 49, 77, 18 });
	insertcoin.PushBack({ 10, 32, 77, 18 });

	insertcoin.PushBack({ 94, 32, 77, 18 });
	insertcoin.PushBack({ 94, 49, 77, 18 });
	insertcoin.speed = 0.15f;

	lives.PushBack({ 107, 4, 8, 16 });

	for (int i = 0; i < 10; i++){
		player1lives.PushBack({ 4 + i * 8, 4, 8, 15 });
	}

	player1blink.PushBack({ 138, 16, 56, 8 });
	player1blink.PushBack({ 0, 0, 0, 0 });
	player1blink.speed = 0.05;
	top.PushBack({ 138, 5, 24, 8 });
	bomb.PushBack({ 122, 4, 8, 16 });

	energybar.PushBack({ 4, 71, 92, 8 });
	energy.PushBack({ 101, 71, 1, 8 });

	goahead.PushBack({ 4, 87, 50, 48 });
	goahead.PushBack({ 0, 0, 0, 0 });
	goahead.speed = 0.1f;

	lowenergy.PushBack({ 4, 155, 44, 27 });
	lowenergy.PushBack({ 0, 0, 0, 0 });
	lowenergy.speed = 0.05f;
}

ModuleLevel1f::~ModuleLevel1f()
{}

bool ModuleLevel1f::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	t = 0, t1 = 0, t2 = 0, t3 = 21, t4 = 13, t5 = 0;

	graphics = App->textures->Load("Sprites/Maps/map1_foreground.png");
	graphics2 = App->textures->Load("Sprites/UI/UI.png");
	low_energy = App->audio->LoadFX("Audio/FX/Low_energy.wav");

	bool wave33 = true;

	return ret;
}

bool ModuleLevel1f::CleanUp()
{
	LOG("Unloading world1");
	App->textures->Unload(graphics);

	return true;
}


update_status ModuleLevel1f::Update()
{
	//World
	App->render->Blit(graphics, 0, -3850, &World1, -1.0f);
	player1lives.setframe(App->player->lives);

	//UI
	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);

	App->render->Blit(graphics2, 160, 0, &insertcoin.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 8, 1, &player1lives.GetActualFrame(), -1.0f, false);
	App->render->Blit(graphics2, 0, 0, &lives.GetCurrentFrame(), -1.0f, false);
	
	App->fonts->Blit(24, 8, 0, App->player->score_text);
	App->fonts->Blit(24, 0, 0, "player1");
	
	App->render->Blit(graphics2, 104, 1, &top.GetCurrentFrame(), -1.0f, false);

	App->render->Blit(graphics2, 24, 1, &player1blink.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 0, 16, &energybar.GetCurrentFrame(), -1.0f, false);

	if (App->player->score < 200000)
	{
		App->fonts->Blit(96, 8, 0, "200000");
	}
	else
	{
		App->fonts->Blit(96, 8, 0, App->player->score_text);
	}

	for (int i = 0; i < App->player->bombs; i++)
	{
		App->render->Blit(graphics2, i * 8, SCREEN_HEIGHT - 16, &bomb.GetCurrentFrame(), -1.0f, false);
	}
	for (int i = 0; i < App->player->energy; i++)
	{
		App->render->Blit(graphics2, 18 + i * 2, 16, &energy.GetCurrentFrame(), -1.0f, false);
	}

	// Go ahead -----------------------------------------

	if (App->player->position.y > 160 + (App->render->camera.y / -2))
	{
		t++;
		if (t > 400)
			App->render->Blit(graphics2, SCREEN_WIDTH / 2 - 25, 50, &goahead.GetCurrentFrame(), -1.0f, false);
	}
	else
		t = 0;

	// Low energy ----------------------------------------

	if (App->player->energy < 8 && App->player->energy > 5)
	{
		App->render->Blit(graphics2, 18, 25, &lowenergy.GetCurrentFrame(), -1.0f, false);
		if (t1 == 35)
		{
			App->audio->PlayFX(low_energy);
			t1 = 0;
		}
		t1++;
	}

	else if (App->player->energy < 6 && App->player->energy > 2)
	{
		lowenergy.speed = 0.09f;
		App->render->Blit(graphics2, 18, 25, &lowenergy.GetCurrentFrame(), -1.0f, false);
		if (t3 == 28)
		{
			App->audio->PlayFX(low_energy);
			t3 = 0;
		}
		t3++;
	}

	else if (App->player->energy < 3 && App->player->energy > 0)
	{
		lowenergy.speed = 0.15f;
		App->render->Blit(graphics2, 18, 25, &lowenergy.GetCurrentFrame(), -1.0f, false);
		if (t4 == 16)
		{
			App->audio->PlayFX(low_energy);
			t4 = 0;
		}
		t4++;
	}

	else if (App->player->energy == 0)
	{
		lowenergy.setframe(0);
		App->render->Blit(graphics2, 18, 25, &lowenergy.GetCurrentFrame(), -1.0f, false);
		if (t5 == 9 && t2 < 200)
		{
			App->audio->PlayFX(low_energy);
			t5 = 0;
		}
		t5++;
		t2++;
	}


		return UPDATE_CONTINUE;
}

