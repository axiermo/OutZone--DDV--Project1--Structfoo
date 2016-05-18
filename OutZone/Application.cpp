#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleTitle.h"
#include "ModuleLevel1b.h"
#include "ModuleLevel1f.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"

Application::Application()
{ 
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = scene_title = new ModuleTitle();
	modules[i++] = scene_level1b = new ModuleLevel1b();
	modules[i++] = scene_gameover = new ModuleGameOver();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = scene_level1f = new ModuleLevel1f();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = fade = new ModuleFadeToBlack();
}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	player->Disable();

	scene_gameover->Disable();
	scene_level1b->Disable();
	collision->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}