#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
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

	down.PushBack({ 55, 139, 31, 39 });
	down.PushBack({ 93, 141, 28, 39 });
	down.PushBack({ 126, 143, 27, 37 });
	down.PushBack({ 159, 143, 28, 39 });
	down.PushBack({ 194, 145, 28, 39 });
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
	graphics = App->textures->Load("Sprites/Character/Moves.png"); 

	basic_laser = App->audio->LoadFX("Audio/FX/Laser.wav");

	position.x = 100;
	position.y = 220;
	curr_animation = &up;

	self = App->collision->AddCollider({position.x + 9, position.y + 1, 12, 29 }, COLLIDER_PLAYER, this);

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

	int speed = 4;
	direction = IDLE;
	last_position = position;
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_REPEAT){
		if (App->player->self->type == COLLIDER_PLAYER)
			App->player->self->type = COLLIDER_GOD;
		
	}


	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE))
		if (position.x < SCREEN_WIDTH - 30)
			SelectAnimation(direction = RIGHT);

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE))
		if (position.x > 0)
			SelectAnimation(direction = LEFT);

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
	{
		if (position.y < 160 + (App->render->camera.y / -2))
		{
			App->render->camera.y += speed;
		}
		SelectAnimation(direction = UP);

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) SelectAnimation(direction = UP_LEFT);
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) SelectAnimation(direction = UP_RIGHT);
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	{
		if (position.y < (App->render->camera.y / -2) + 288)
		{
			SelectAnimation(direction = DOWN);
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) SelectAnimation(direction = DOWN_LEFT);
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) SelectAnimation(direction = DOWN_RIGHT);
	}

	// FIRE -------------------------------------------------------

	curr_laser = SDL_GetTicks();

	if (curr_laser - last_laser > 150)
	{
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &up)) Fire(UP);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &down)) Fire(DOWN);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &left)) Fire(LEFT);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &right)) Fire(RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &upright)) Fire(UP_RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &upleft)) Fire(UP_LEFT);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &downright)) Fire(DOWN_RIGHT);
		if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (curr_animation == &downleft)) Fire(DOWN_LEFT);
	}

	// DRAW -------------------------------------------------------------

	if (direction != IDLE)
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetCurrentFrame()));
	else
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetActualFrame()));

	// MODIFY COLLISION -------------------------------------------------

	self->SetPos(position.x + 9, position.y + 1);

	return UPDATE_CONTINUE;
}

void ModulePlayer::SelectAnimation(Directions direction)
{
	int speed = 2;
	last_animation = curr_animation;

	switch (direction)
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
		App->particles->AddParticle(App->particles->laserup, position.x + 18, position.y - 10, { 0, -5 }, { 0, 0, 6, 18 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosionup, position.x +12, position.y -15, { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case DOWN:
		App->particles->AddParticle(App->particles->laserup, position.x + 5, position.y + 19, { 0, +5 }, { 0, 0, 6, 18 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosiondown, position.x -1 , position.y + 28 , { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case LEFT:
		App->particles->AddParticle(App->particles->laserright, position.x - 8, position.y + 5, { -5, 0 }, { 0, 0, 18, 6 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosionleft, position.x -15, position.y , { 0, 0 } , nullrect, COLLIDER_NONE);
		break;											 
	case RIGHT:											 
		App->particles->AddParticle(App->particles->laserright, position.x + 29, position.y + 10, { +5, 0 }, { 0, 0, 18, 6 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosionright, position.x + 29, position.y +4 , { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case UP_LEFT:
		App->particles->AddParticle(App->particles->laserupleft, position.x + 5, position.y - 10, { -5, -5 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosionupleft, position.x  , position.y -14, { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case UP_RIGHT:
		App->particles->AddParticle(App->particles->laserupright, position.x + 20, position.y - 10, { +5, -5 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosionupright, position.x +20 , position.y-10, { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case DOWN_LEFT:
		App->particles->AddParticle(App->particles->laserupright, position.x - 11, position.y + 12, { -5, +5 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosiondownleft, position.x - 11, position.y + 16, { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	case DOWN_RIGHT:
		App->particles->AddParticle(App->particles->laserupleft, position.x + 12, position.y + 12, { +5, +5 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->explosiondownright, position.x + 17, position.y + 20, { 0, 0 }, nullrect, COLLIDER_NONE);
		break;
	}

	last_laser = SDL_GetTicks();
	App->audio->PlayFX(basic_laser);
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) 
{
	if (self == c1 && self != nullptr && c2->type == COLLIDER_WALL || c2->type == COLLIDER_TURRET || c2->type == COLLIDER_DOOR || c2->type == COLLIDER_TURRET_WALL)
	{
		position = last_position;
	}
}
