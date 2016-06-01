#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	virtual ~ModuleWindow();
	bool Init();
	bool CleanUp();

	bool checkpoint_1;
	bool checkpoint_2;
	bool checkpoint_3;
	bool checkpoint_4;
	bool checkpoint_5;
	bool checkpoint_6;
	bool checkpoint_7;

public:
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;
};

#endif // __ModuleWindow_H__