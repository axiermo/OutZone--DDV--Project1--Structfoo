#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleTitle : public Module
{
public:
	ModuleTitle();
	~ModuleTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;

	Mix_Chunk* insertcoin = nullptr;

	SDL_Rect title;
	Animation creditnums;
	int coins = 0;
	Animation credit;
	Animation pushstart;

	float foreground_pos;
	bool forward;

	bool stop = false;
	uint t = 0;
};

#endif // __ModuleTitle_H__