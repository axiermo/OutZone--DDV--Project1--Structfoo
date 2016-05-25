#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1f.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
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

	player1lives.PushBack({ 20, 4, 8, 16 });

	player1blink.PushBack({ 138, 16, 56, 8 });
	player1blink.PushBack({ 0, 0, 0, 0 });
	player1blink.speed = 0.05;
	top.PushBack({ 138, 5, 24, 8 });
	bomb.PushBack({ 122, 4, 8, 16 });

	energybar.PushBack({ 4, 71, 92, 8 });
	energy.PushBack({ 101, 71, 1, 8 });
}

ModuleLevel1f::~ModuleLevel1f()
{}

bool ModuleLevel1f::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Sprites/Maps/map1_foreground.png");
	graphics2 = App->textures->Load("Sprites/UI/UI.png");


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


	//UI
	sprintf_s(App->player->score_text, 10, "%d", App->player->score);


	App->render->Blit(graphics2, 160, 0, &insertcoin.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 8, 1, &player1lives.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 0, 0, &lives.GetCurrentFrame(), -1.0f, false);
	
	App->fonts->Blit(24, 8, 0, App->player->score_text);
	App->fonts->Blit(24, 0, 0, "player1");
	
	App->render->Blit(graphics2, 104, 1, &top.GetCurrentFrame(), -1.0f, false);

	App->render->Blit(graphics2, 24, 1, &player1blink.GetCurrentFrame(), -1.0f, false);
	App->render->Blit(graphics2, 0, 16, &energybar.GetCurrentFrame(), -1.0f, false);

	if (App->player->score < 200000){
		App->fonts->Blit(96, 8, 0, "200000");
	}
	else{
		App->fonts->Blit(96, 8, 0, App->player->score_text);
	}

	for (int i = 0; i < App->player->bombs; i++){
		App->render->Blit(graphics2, i * 8, SCREEN_HEIGHT - 16, &bomb.GetCurrentFrame(), -1.0f, false);
	}
	for (int i = 0; i < App->player->energy; i++){
		App->render->Blit(graphics2, 18 + i * 2, 16, &energy.GetCurrentFrame(), -1.0f, false);
	}
	return UPDATE_CONTINUE;
}

