#ifndef __ModuleLevel1f_H__
#define __ModuleLevel1f_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel1f : public Module
{
public:
	ModuleLevel1f();
	~ModuleLevel1f();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;

	SDL_Rect World1;
	Animation lives;
	Animation insertcoin;
	Animation player1lives;
	Animation player1blink;
	Animation top;
	Animation bomb;
	Animation energy;
	Animation energybar;
	Animation goahead;
	Animation lowenergy;

	Mix_Chunk* low_energy = nullptr;

	int var = 0;
	
	bool wave = true;
	uint t0, t01 = 0;
	uint t = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
	bool played = false;
};

#endif // __ModuleLevel1f_H__