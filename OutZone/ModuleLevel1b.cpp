#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1b.h"
#include "ModuleLevel1f.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleGameOver.h"
#include "ModuleEnemies.h"

ModuleLevel1b::ModuleLevel1b()
{
	World1 = {0, 0, 256, 4180};
}

ModuleLevel1b::~ModuleLevel1b()
{}

bool ModuleLevel1b::Start()
{
	
	LOG("Loading background assets");
	bool ret = true;
	App->render->camera.y = 0;
	App->particles->Enable();
	// Background
	graphics = App->textures->Load("Sprites/Maps/map1_base.png");

	// Music
	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_1.ogg");
	App->audio->PlayMusic1(soundtrack);

	App->collision->Enable();
	App->player->Enable();
	App->scene_level1f->Enable();
	App->enemies->Enable();

	//--------------Grey Turrets----------------------

	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 4, -578);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 132, -610);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 196, -675);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 132, -992);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 107, -2057);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 43, -2057);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 75, -2018);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 11, -2010);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 147, -2026);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 203, -2002);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 179, -2050);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 155, -2098);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 19, -2098);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 3, -2138);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 75, -2146);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 203, -2130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 139, -2154);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 99, -2106);

	//-----------------Big Turrets-----------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::BIGTURRET, 20, -1320);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGTURRET, 180, -1610);

	//-----------------Door Turrets--------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::DOORTURRET, 60, -3255);
	App->enemies->AddEnemy(ENEMY_TYPES::DOORTURRET, 160, -3255);
	//Soldiers

	//Door
	App->enemies->AddEnemy(ENEMY_TYPES::DOOR, 73, -3347);

	// Blue destroyed ship
	App->collision->AddCollider({ 0, 56, 16, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -86, 64, 142 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -164, 64, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -141, 25, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -117, 32, 173 }, COLLIDER_WALL);
	App->collision->AddCollider({ 171, -138, 85, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, -86, 95, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 168, -66, 88, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 177, -54, 79, 27 }, COLLIDER_WALL);
	App->collision->AddCollider({ 193, -27, 63, 15 }, COLLIDER_WALL);

	// Columns
	App->collision->AddCollider({ 128, -714, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -779, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -906, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -1065, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 63, -1733, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -1764, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -1796, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 96, -1892, 32, 54 }, COLLIDER_WALL);

	// Defense tower
	App->collision->AddCollider({ 0, -1207, 32, 34 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 0, -1331, 125, 124 }, COLLIDER_TURRET_WALL); // Left Tower
	App->collision->AddCollider({ 0, -1349, 121, 18 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 198, -1351, 58, 145 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 134, -1637, 122, 143 }, COLLIDER_TURRET_WALL); // Right Tower
	App->collision->AddCollider({ 0, -1636, 58, 20 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 0, -1616, 62, 121 }, COLLIDER_TURRET_WALL); // Pipiru

	//Gate
	App->collision->AddCollider({ 0, -3333, 30, 64 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, -3333, 63, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -3333, 66, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 226, -3333, 30, 64 }, COLLIDER_WALL);

	return ret;
}

bool ModuleLevel1b::CleanUp()
{
	LOG("Unloading world1");
	App->textures->Unload(graphics);

	App->collision->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->scene_level1f->Disable();

	return true;
}

update_status ModuleLevel1b::Update()
{
	App->render->Blit(graphics, 0, -3850, &World1,-1.0f,true);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->player->position.y < -3640 || App->player->destroyed)
	{
		App->fade->FadeToBlack(App->scene_level1b, App->scene_gameover, 2.0);
	}
	return UPDATE_CONTINUE;
}