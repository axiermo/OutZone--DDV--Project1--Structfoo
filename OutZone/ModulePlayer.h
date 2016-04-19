#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation forwardright;
	Animation right;
	Animation downright;
	Animation down;
	Animation downleft;
	Animation left;
	Animation forwardleft;
	Animation backward;
	iPoint position;

};

#endif