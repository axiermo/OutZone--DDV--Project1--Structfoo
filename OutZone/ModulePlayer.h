#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	void OnCollision(Collider* c1, Collider* c2);
	bool CleanUp();

	void SelectAnimation(Directions direction);
	void Fire(Directions dir);

	bool weapon;
	uint laser;
	uint damage;

public:
	enum Directions direction;

	SDL_Texture* graphics = nullptr;
	Mix_Chunk* basic_laser = nullptr;
	Mix_Chunk* triple_laser = nullptr;

	Animation idle;
	Animation up;
	Animation upright;
	Animation right;
	Animation downright;
	Animation down;
	Animation downleft;
	Animation left;
	Animation upleft;

	Animation up2;
	Animation right2;
	Animation down2;
	Animation left2;

	Animation lowenergydead;

	int font_score = -1;
	char score_text[10];
	char cameray[10];
	uint score = 0;
	uint bombs = 3;
	int energy = 36;
	int lives = 3;

	uint t0;
	uint t1;
	uint tt0;
	uint tt1;

	Animation* curr_animation = nullptr;
	Animation* last_animation = nullptr;
	Animation* aux = nullptr;

	Collider* self;
	bool destroyed = false;

	iPoint position;
	iPoint last_position;

	uint last_laser;
	uint curr_laser;

	bool checkpoint_1 = false;
	bool checkpoint_2 = false;
	bool checkpoint_3 = false;
	bool checkpoint_4 = false;
	bool checkpoint_5 = false;
	bool checkpoint_6 = false;
	bool checkpoint_7 = false;
};

#endif