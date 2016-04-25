#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void SelectAnimation(Directions direction);
	void Fire(Directions direction);
	void Fire();

public:
	enum Directions direction;

	SDL_Texture* graphics = nullptr;
	Mix_Chunk* basic_laser = nullptr;

	Animation idle;
	Animation up;
	Animation upright;
	Animation right;
	Animation downright;
	Animation down;
	Animation downleft;
	Animation left;
	Animation upleft;

	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;

	iPoint position;

	uint last_laser;
	uint curr_laser;
};

#endif