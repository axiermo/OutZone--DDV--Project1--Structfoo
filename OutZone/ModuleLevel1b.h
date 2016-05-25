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
	bool wave1;
	bool wave2;
	bool wave3;
	bool wave4;
	bool wave5;
	bool wave6;
	bool wave7;
	bool wave8;
	bool wave9;
	bool wave10;
	bool wave11;
	bool wave12;
	bool wave13;
	bool wave14;
	bool wave15;

public:
	Collider* lborder;
	Collider* rborder;
	Collider* sborder;
	Collider* nborder;
	Mix_Music* soundtrack;
	SDL_Texture* graphics = nullptr;
	SDL_Rect World1;
};

#endif // __ModuleLevel1b_H__