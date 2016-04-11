#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "FinalScreen.h"

ModuleFinalScreen::ModuleFinalScreen()
{
	// ground
	FinalScreen = { 0, 0, 240, 320 };


}

ModuleFinalScreen::~ModuleFinalScreen()
{}

// Load assets
bool ModuleFinalScreen::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("fake_final_screen.png");//cambiar a final screen//WE NEED TO CHANGE THIS IMAGE

	// TODO 1: Enable (and properly disable) the player module
	((Module*)App->player)->Enable();
	return ret;
}

// Load assets
bool ModuleFinalScreen::CleanUp()
{
	LOG("Unloading Final Screen");
	((Module*)App->player)->Disable();
	return true;
}

// Update: draw background
update_status ModuleFinalScreen::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &FinalScreen);
	//App->render->Blit(graphics, 50, -15, &background, 0.75f); // back of the room
	//App->render->Blit(graphics, 280, 125, &foreground);
	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	//App->render->Blit(graphics, 0, -16, &roof, 0.75f);

	return UPDATE_CONTINUE;
}