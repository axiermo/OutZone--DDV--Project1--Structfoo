#ifndef __ModuleGameOver_H__
#define __ModuleGameOver_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Music* soundtrack;

	SDL_Rect GameOverScreen;

	float foreground_pos;
	bool forward;
};

#endif // __ModuleGameOver_H__