#ifndef __ModuleLevel1b_H__
#define __ModuleLevel1b_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel1b : public Module
{
public:
	ModuleLevel1b();
	~ModuleLevel1b();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Collider* lborder;
	Collider* rborder;
	Collider* sborder;
	Mix_Music* soundtrack;
	SDL_Texture* graphics = nullptr;
	SDL_Rect World1;
};

#endif // __ModuleLevel1b_H__