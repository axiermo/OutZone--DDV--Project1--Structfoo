#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleTitle;
class ModuleLevel1b;
class ModuleLevel1f;
class ModuleAudio;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleLevel2b;
class ModuleCollision;
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
	ModuleLevel1b* scene_level1b;
	ModuleLevel1f* scene_level1f;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleLevel2b* scene_level2b;
	ModuleParticles* particles;
	ModuleCollision* collision;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application
extern Application* App;

#endif // __APPLICATION_H__