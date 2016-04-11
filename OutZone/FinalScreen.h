#ifndef __FinalScreen_H__
#define __FinalScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleFinalScreen : public Module
{
public:
	ModuleFinalScreen();
	~ModuleFinalScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect FinalScreen;

	//Animation water;
};

#endif // __FinalScreen_H__