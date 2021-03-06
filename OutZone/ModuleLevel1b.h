#ifndef __ModuleLevel1b_H__
#define __ModuleLevel1b_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel1b : public Module
{
public:
	ModuleLevel1b();
	~ModuleLevel1b();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool wave1;
	bool wave2;
	bool wave3;
	bool wave4;
	bool wave5;
	bool wave6;
	bool wave7;
	bool wave8;
	bool wave9;
	bool wave10;
	bool wave11;
	bool wave12;
	bool wave13;
	bool wave14;
	bool wave15;
	bool wave16;
	bool wave17;
	bool wave18;
	bool wave19;
	bool wave20;
	bool wave21;
	bool wave22;
	bool wave23;
	bool wave24;
	bool wave25;
	bool wave26;
	bool wave27;
	bool wave28;
	bool wave29;
	bool wave30;
	bool wave31;
	bool wave32;
	bool wave33; //first truck
	bool wave34;
	bool wave35;
	bool wave36;
	bool wave37;
	bool wave38;
	bool wave39;
	bool wave40;
	bool wave41;
	bool wave42;

	uint t0, t1 = 0, numtanks = 0, t2 = 0;
	bool done = false;
	bool done2 = false;

public:
	Collider* lborder;
	Collider* rborder;
	Collider* sborder;
	Collider* nborder;
	Mix_Music* soundtrack;
	SDL_Texture* graphics = nullptr;
	SDL_Rect World1;
};

#endif // __ModuleLevel1b_H__