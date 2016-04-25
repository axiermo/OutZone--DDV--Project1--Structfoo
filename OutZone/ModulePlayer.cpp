#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
	// Character sprites
	up.PushBack({ 17, 273, 29, 38 });
	up.PushBack({ 55, 274, 27, 37 });
	up.PushBack({ 90, 274, 27, 37 });
	up.PushBack({ 126, 273, 26, 37 });
	up.PushBack({ 161, 274, 28, 37 });
	up.speed = 0.2f;

	right.PushBack({ 92, 230, 28, 35 });
	right.PushBack({ 128, 230, 30, 36 });
	right.PushBack({ 165, 231, 30, 35 });
	right.PushBack({ 202, 230, 29, 37 });
	right.PushBack({ 55, 231, 29, 35 });
	right.speed = 0.2f;

	left.PushBack({ 166, 191, 29, 35 });
	left.PushBack({ 131, 192, 32, 33 });
	left.PushBack({ 93, 191, 28, 35 });
	left.PushBack({ 55, 192, 29, 35 });
	left.PushBack({ 18, 191, 27, 35 });
	left.speed = 0.2f;

	down.PushBack({ 54, 139, 31, 39 });
	down.PushBack({ 92, 141, 28, 39 });
	down.PushBack({ 125, 143, 27, 37 });
	down.PushBack({ 156, 143, 28, 39 });
	down.PushBack({ 193, 145, 28, 39 });
	down.speed = 0.2f;

	upleft.PushBack({ 57, 93, 29, 36 });
	upleft.PushBack({ 90, 93, 30, 37 });
	upleft.PushBack({ 123, 92, 30, 37 });
	upleft.PushBack({ 156, 91, 31, 35 });
	upleft.PushBack({ 202, 190, 28, 36 });
	upleft.speed = 0.2f;

	downleft.PushBack({ 193, 90, 30, 37 });
	downleft.PushBack({ 20, 372, 30, 37 });
	downleft.PushBack({ 53, 374, 31, 38 });
	downleft.PushBack({ 91, 374, 31, 39 });
	downleft.PushBack({ 128, 376, 28, 37 });
	downleft.speed = 0.2f;

	downright.PushBack({ 18, 41, 25, 38 });
	downright.PushBack({ 51, 44, 28, 38 });
	downright.PushBack({ 86, 45, 28, 37 });
	downright.PushBack({ 121, 45, 27, 37 });
	downright.PushBack({ 157, 46, 27, 37 });
	downright.speed = 0.2f;

	upright.PushBack({ 20, 329, 24, 37 });
	upright.PushBack({ 50, 326, 25, 38 });
	upright.PushBack({ 82, 325, 24, 36 });
	upright.PushBack({ 114, 323, 25, 37 });
	upright.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	graphics = App->textures->Load("Sprites/Character/Moves.png"); // arcade version
	basic_laser = App->audio->LoadFX("Audio/FX/Laser.wav");

	position.x = 100;
	position.y = 220;
	curr_animation = &up;
	direction = IDLE;

	last_laser = SDL_GetTicks();

	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player textures");
	App->textures->Unload(graphics);

	return true;
}

update_status ModulePlayer::Update()
{
	// MOVEMENT ---------------------------------------------------

	direction = IDLE;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE))
		SelectAnimation(direction = RIGHT);

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE))
		SelectAnimation(direction = LEFT);

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
	{
		SelectAnimation(direction = UP);

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) SelectAnimation(direction = UP_LEFT);
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) SelectAnimation(direction = UP_RIGHT);
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
	{
		SelectAnimation(direction = DOWN);

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) SelectAnimation(direction = DOWN_LEFT);
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) SelectAnimation(direction = DOWN_RIGHT);
	}

	// FIRE -------------------------------------------------------

	curr_laser = SDL_GetTicks();

	if (curr_laser - last_laser > 150)
	{
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &up)) Fire(UP);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &down)) Fire(DOWN);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &left)) Fire(LEFT);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &right)) Fire(RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &upright)) Fire(UP_RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &upleft)) Fire(UP_LEFT);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &downright)) Fire(DOWN_RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) && (curr_animation == &downleft)) Fire(DOWN_LEFT);
	}

	// DRAW -------------------------------------------------------------

	if (direction != IDLE)
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetCurrentFrame()));
	else
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetActualFrame(1)));

	return UPDATE_CONTINUE;
}

void ModulePlayer::SelectAnimation(Directions direction)
{
	int speed = 2;
	last_animation = curr_animation;

	switch(direction)
	{
	case UP:
		curr_animation = &up;
		position.y -= speed;
		break;
	case DOWN:
		curr_animation = &down;
		position.y += speed;
		break;
	case LEFT:
		curr_animation = &left;
		position.x -= speed;
		break;
	case RIGHT:
		curr_animation = &right; 
		position.x += speed;
		break;
	case UP_LEFT:
		curr_animation = &upleft;
		break;
	case UP_RIGHT:
		curr_animation = &upright;
		break;
	case DOWN_LEFT:
		curr_animation = &downleft;
		break;
	case DOWN_RIGHT:
		curr_animation = &downright;
		break;
	}
}

void ModulePlayer::Fire(Directions direction)
{
	switch (direction)
	{
	case UP:
		App->particles->AddParticle(App->particles->laser90, position.x + 20, position.y - 10, { 0, -5 });
		break;
	case DOWN:
		App->particles->AddParticle(App->particles->laser90, position.x + 7, position.y + 19, { 0, +5 });
		break;
	case LEFT:
		App->particles->AddParticle(App->particles->laser0, position.x - 5, position.y + 5, { -5, 0 });
		break;
	case RIGHT:
		App->particles->AddParticle(App->particles->laser0, position.x + 20, position.y + 10, { +5, 0 });
		break;
	case UP_LEFT:
		App->particles->AddParticle(App->particles->laser135, position.x + 7, position.y - 5, { -5, -5 });
		break;
	case UP_RIGHT:
		App->particles->AddParticle(App->particles->laser45, position.x + 20, position.y - 10, { +5, -5 });
		break;
	case DOWN_LEFT:
		App->particles->AddParticle(App->particles->laser45, position.x - 11, position.y + 8, { -5, +5 });
		break;
	case DOWN_RIGHT:
		App->particles->AddParticle(App->particles->laser135, position.x + 10, position.y + 10, { +5, +5 });
		break;
	}

	last_laser = SDL_GetTicks();
	App->audio->PlayFX(basic_laser);
}