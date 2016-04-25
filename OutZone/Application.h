#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleAudio;
class ModuleTitle;
class ModuleLevel1;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleFinalScreen;
class ModuleParticles;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleTextures* textures;
	ModuleTitle* scene_title;
	ModuleLevel1* scene_level1;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleFinalScreen* final_screen;
	ModuleParticles* particles;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__