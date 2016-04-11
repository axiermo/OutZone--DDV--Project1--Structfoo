#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "FinalScreen.h"

ModuleLevel1::ModuleLevel1()
{
	World1 = {0, 0, 240, 3896};
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("level1.png");

	// TODO 1: Enable (and properly disable) the player module
	((Module*)App->player)->Enable(); 
	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading world1");
	((Module*)App->player)->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -3576, &World1);
	//App->render->Blit(graphics, 50, -15, &background, 0.75f); // back of the room
	//App->render->Blit(graphics, 280, 125, &foreground);
	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	//App->render->Blit(graphics, 0, -16, &roof, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_level1, App->final_screen, 2.0F);
	}
	return UPDATE_CONTINUE;
}