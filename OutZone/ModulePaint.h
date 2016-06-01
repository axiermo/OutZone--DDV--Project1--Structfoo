#ifndef __ModulePaint_H__
#define __ModulePaint_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "p2Point.h"

#define MAX_ACTIVE_PAINT 300

struct SDL_Texture;

struct Paint
{
	Animation anim;
	iPoint position;

	Paint();
	Paint(const Paint& p);
	~Paint() {};
};

class ModulePaint : public Module
{
public:
	ModulePaint();
	~ModulePaint();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddPaint(const Paint& particle, int x, int y, Uint32 delay = 0);

	Paint* active[MAX_ACTIVE_PAINT];

public:
	SDL_Texture* graphics = nullptr;

	Paint truck_hole;
	Paint turret_hole;
	Paint truck_mark;
	Paint mazurka_hole;
};

#endif // __ModulePaint_H__