#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"



ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({12, 8, 33, 35});


	forward.PushBack({ 12, 8, 33, 35 });
	forward.PushBack({ 53, 8, 31, 30 });
	forward.PushBack({ 92, 8, 31, 34 });
	forward.PushBack({ 132, 8, 30, 33 });
	forward.PushBack({ 170, 8, 32, 31 });
	forward.speed = 0.1f;

	forwardright.PushBack({ 12, 47, 32, 33 });
	forwardright.PushBack({ 55, 46, 27, 32 });
	forwardright.PushBack({ 88, 46, 25, 30 });
	forwardright.PushBack({ 124, 47, 27, 29 });
	forwardright.PushBack({ 161, 46, 29, 32 });
	forwardright.speed = 0.1f;

	right.PushBack({ 12, 84, 33, 31 });
	right.PushBack({ 54, 83, 30, 30 });
	right.PushBack({ 95, 83, 29, 32 });
	right.PushBack({ 130, 84, 31, 29 });
	right.PushBack({ 171, 83, 30, 32 });
	right.speed = 0.1f;

	downright.PushBack({ 14, 122, 30, 32 });
	downright.PushBack({53 ,121 ,30 ,30 });
	downright.PushBack({ 92,121 ,29 ,30 });
	downright.PushBack({ 132,122 ,29 ,33 });
	downright.PushBack({ 170,121 ,28 ,30 });
	downright.speed = 0.1f;

	down.PushBack({ 12, 158,33 ,34 });
	down.PushBack({ 51,158 ,31 ,30 });
	down.PushBack({89 ,158 ,31 ,32 });
	down.PushBack({127 ,158 ,32 ,34 });
	down.PushBack({ 166,158 ,33 ,30 });
	down.speed = 0.1f;
	
	downleft.PushBack({11 , 200, 35, 35});
	downleft.PushBack({49 ,200 , 33,33 });
	downleft.PushBack({87 ,200 ,30 , 31});
	downleft.PushBack({ 126, 201, 32, 32});
	downleft.PushBack({ 165,200 ,33 ,30 });
	downleft.speed = 0.1f;

	left.PushBack({ 13, 241, 33, 30 });
	left.PushBack({ 51, 240, 32, 30 });
	left.PushBack({ 90, 240, 31, 30 });
	left.PushBack({ 130, 241, 30, 28 });
	left.PushBack({ 167, 240, 31, 28 });
	left.speed = 0.1f;

	forwardleft.PushBack({17 ,276 ,28 ,34 });
	forwardleft.PushBack({ 51, 275, 31, 35});
	forwardleft.PushBack({ 88, 275, 32, 35});
	forwardleft.PushBack({ 129, 276, 32, 34});
	forwardleft.PushBack({ 170, 275, 29, 33});
	forwardleft.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("MainCharacter.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;




	

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &right;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &left;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &forward;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &down;
		position.y += speed;
	}
	if ((App->input->keyboard[SDL_SCANCODE_D] == 1) && (App->input->keyboard[SDL_SCANCODE_W] == 1)){
		current_animation = &forwardright;

	}
	if ((App->input->keyboard[SDL_SCANCODE_A] == 1) && (App->input->keyboard[SDL_SCANCODE_W] == 1)){
		current_animation = &forwardleft;

	}
	if ((App->input->keyboard[SDL_SCANCODE_D] == 1) && (App->input->keyboard[SDL_SCANCODE_S] == 1)){
		current_animation = &downright;

	}
	if ((App->input->keyboard[SDL_SCANCODE_A] == 1) && (App->input->keyboard[SDL_SCANCODE_S] == 1)){
		current_animation = &downleft;

	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}