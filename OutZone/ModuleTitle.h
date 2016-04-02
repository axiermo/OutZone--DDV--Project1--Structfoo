#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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
	SDL_Rect ground;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation flag;
	Animation girl;

	float foreground_pos;
	bool forward;
};

#endif // __ModuleTitle_H__