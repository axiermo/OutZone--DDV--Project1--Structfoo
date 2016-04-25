#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "FinalScreen.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ModuleLevel1::ModuleLevel1()
{
	World1 = {0, 0, 256, 4180};
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	//Background
	graphics = App->textures->Load("Sprites/Maps/map1_base.png");

	//Music
	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_1.ogg");
	App->audio->PlayMusic(soundtrack);
	((Module*)App->player)->Enable();

	//Collisions
	App->collision->Enable();

	//Blue destroyed ship
	App->collision->AddCollider({ 0, 3906, 16, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 3764, 64, 142 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 3686, 64, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, 3709, 25, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, 3733, 32, 173 }, COLLIDER_WALL);
	App->collision->AddCollider({ 171, 3712, 85, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, 3764, 95, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 168, 3784, 88, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 177, 3796, 79, 27 }, COLLIDER_WALL);
	App->collision->AddCollider({ 193, 3823, 63, 15 }, COLLIDER_WALL);

	//Columns
	App->collision->AddCollider({ 128, 3136, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, 3071, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 2944, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, 2785, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 63, 2117, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, 2086, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 2054, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 96, 1958, 32, 54 }, COLLIDER_WALL);

	//Defense tower
	App->collision->AddCollider({ 0, 2643, 32, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 2519, 125, 124 }, COLLIDER_WALL); //<- Left Tower
	App->collision->AddCollider({ 0, 2501, 121, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 198, 2499, 58, 145 }, COLLIDER_WALL);
	App->collision->AddCollider({ 134, 2213, 122, 143 }, COLLIDER_WALL); //<- Right Tower
	App->collision->AddCollider({ 0, 2214, 58, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 2234, 62, 121 }, COLLIDER_WALL); // <- Pipiru

	//Gate
	App->collision->AddCollider({ 0, 517, 30, 64 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, 517, 63, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, 517, 66, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 226, 517, 30, 64 }, COLLIDER_WALL);

	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading world1");
	((Module*)App->player)->Disable();
	App->collision->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -3850, &World1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_level1, App->final_screen, 2.0F);
	}
	return UPDATE_CONTINUE;
}