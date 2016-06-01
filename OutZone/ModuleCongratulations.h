#ifndef __ModuleCongratulations_H__
#define __ModuleCongratulations_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCongratulations : public Module
{
public:
	ModuleCongratulations();
	~ModuleCongratulations();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Animation top;
	Animation player1;
	Animation player2;
	Mix_Music* soundtrack;

	SDL_Rect GameOverScreen;

	float foreground_pos;
	bool forward;
};

#endif