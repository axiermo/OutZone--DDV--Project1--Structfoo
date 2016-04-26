#ifndef __FinalScreen_H__
#define __FinalScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel2b : public Module
{
public:
	ModuleLevel2b();
	~ModuleLevel2b();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* soundtrack;
	SDL_Texture* graphics = nullptr;
	SDL_Rect FinalScreen;
};

#endif // __FinalScreen_H__