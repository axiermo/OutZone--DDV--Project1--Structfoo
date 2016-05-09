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

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = scene_title = new ModuleTitle();
	modules[6] = scene_level1b = new ModuleLevel1b();
	modules[7] = scene_gameover = new ModuleGameOver();
	modules[8] = player = new ModulePlayer();
	modules[9] = particles = new ModuleParticles();
	modules[10] = scene_level1f = new ModuleLevel1f();
	modules[11] = enemies = new ModuleEnemies();
	modules[12] = collision = new ModuleCollision();
	modules[13] = fade = new ModuleFadeToBlack();
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