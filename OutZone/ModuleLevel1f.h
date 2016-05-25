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
};

#endif // __ModuleLevel1f_H__