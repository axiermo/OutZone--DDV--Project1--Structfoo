#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleExplosion.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer()
{
	// 1st weapon
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

	//2nd weapon
	up2.PushBack({ 19, 432, 30, 37 });
	up2.PushBack({ 62, 432, 30, 37 });
	up2.PushBack({ 103, 431, 30, 37 });
	up2.PushBack({ 146, 431, 30, 36 });
	up2.PushBack({ 191, 432, 30, 37 });
	up2.speed = 0.2f;

	right2.PushBack({ 19, 488, 30, 37 });
	right2.PushBack({ 62, 489, 30, 36 });
	right2.PushBack({ 102, 488, 30, 37 });
	right2.PushBack({ 146, 488, 30, 37 });
	right2.PushBack({ 191, 489, 30, 37 });
	right2.speed = 0.2f;

	left2.PushBack({ 21, 544, 30, 36 });
	left2.PushBack({ 63, 543, 30, 37 });
	left2.PushBack({ 105, 543, 30, 37 });
	left2.PushBack({ 147, 543, 30, 37 });
	left2.PushBack({ 189, 543, 30, 37 });
	left2.speed = 0.2f;

	down2.PushBack({ 22, 594, 30, 37 });
	down2.PushBack({ 64, 594, 30, 37 });
	down2.PushBack({ 108, 594, 30, 37 });
	down2.PushBack({ 150, 594, 30, 37 });
	down2.PushBack({ 189, 595, 30, 36 });
	down2.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Character/Moves.png");

	basic_laser = App->audio->LoadFX("Audio/FX/Laser.wav");

	if (checkpoint4 == true){
		position.x = 114;
		position.y = -3338;
	}
	else if (checkpoint3 == true){
		position.x = 113;
		position.y = -2246;
	}
	else if (checkpoint2 == true){
		position.x = 139;
		position.y = -1346;
	}
	else if (checkpoint1 == true){
		position.x = 75;
		position.y = -734;
	}
	else{
		position.x = 100;
		position.y = 220;
	}

	curr_animation = &up;

	weapon = false;
	laser = 1;
	damage = 2;

	self = App->collision->AddCollider({ position.x + 9, position.y + 1, 12, 29 }, COLLIDER_PLAYER, this);

	font_score = App->fonts->Load("OutZoneScoreFont.png", "!_#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz^ ", 1);
	font_score = App->fonts->Load("OutZoneScoreFontGreen.png", "!_#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz^ ", 1);
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

	switch (weapon)
	{
	case false: // 1st weapon
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
		break;
	case true: // 2nd weapon
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
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		{
			if (position.y < (App->render->camera.y / -2) + 288)
			{
				SelectAnimation(direction = DOWN);
			}
		}
		break;
	}

	// God mode ----------------------------------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_REPEAT)
	{
		if (App->player->self->type == COLLIDER_PLAYER)
			App->player->self->type = COLLIDER_GOD;
	}
	if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_REPEAT)
	{
		if (App->player->self->type == COLLIDER_GOD)
			App->player->self->type = COLLIDER_PLAYER;
	}

	// Airstrike ---------------------------------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_UP)
	{
		if (App->player->bombs > 0)
		{
			App->explosion->AddExplosion(App->explosion->Airstrike, App->render->camera.x, (-App->render->camera.y * 2 / speed), { 0, 0 }, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, COLLIDER_EXPLOSION);
			App->player->bombs--;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_UP)
		bombs++;

	// Energy ----------------------------------------------------------------

	t0 = SDL_GetTicks();
	if (t0 - t1 > 1600){
		energy--;
		t1 = SDL_GetTicks();
	}

	// Teleport --------------------------------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_UP)
	{
		App->render->camera.y = 1500;
		App->player->position.y = -700;
	}
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_UP)
	{
		App->render->camera.y = 2700;
		App->player->position.y = -1200;
	}
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_STATE::KEY_UP)
	{
		App->render->camera.y = 3250;
		App->player->position.y = -1450;
	}
	if (App->input->keyboard[SDL_SCANCODE_4] == KEY_STATE::KEY_UP)
	{
		App->render->camera.y = 6700;
		App->player->position.y = -3150;
	}
	// Damage -----------------------------------------------------

	if (!weapon)
	{
		if (laser == 1) damage = 2;
		else if (laser == 2) damage = 3;
		else damage = 4;
	}
	else
	{
		if (laser == 1) damage = 1;
		else if (laser == 2) damage = 2;
		else damage = 3;
	}

	// FIRE -------------------------------------------------------

	curr_laser = SDL_GetTicks();

	int x;
	if (direction == IDLE || curr_animation == last_animation) x = 100;  
	else x = 40;

	switch (weapon)
	{
	case false:
		if (curr_laser - last_laser > x)
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
		break;
	case true:
		if (curr_laser - last_laser > 600 && App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
			Fire(UP);
		else if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
			Fire(UP);
		break;
	}

	// DRAW -------------------------------------------------------------

	if (direction != IDLE)
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);
	else
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetActualFrame()), -1.0f);

	// MODIFY COLLISION -------------------------------------------------

	self->SetPos(position.x + 9, position.y + 1);

	return UPDATE_CONTINUE;
}

void ModulePlayer::SelectAnimation(Directions direction)
{
	int speed = 2;
	tt0 = SDL_GetTicks();
	if (tt0 - tt1 > 40){
		last_animation = curr_animation;
		tt1 = SDL_GetTicks();
	}

	switch (weapon)
	{
	case false:
		switch (direction)
		{
		case UP:
			if (last_animation == &left) curr_animation = &upleft;
			else if (last_animation == &right) curr_animation = &upright;
			else if (last_animation == &downright) curr_animation = &right;
			else if (last_animation == &downleft) curr_animation = &left;
			else if (last_animation == &down) curr_animation = &downright;
			else curr_animation = &up;
			position.y -= speed;
			break;
		case DOWN:
			if (last_animation == &left) curr_animation = &downleft;
			else if (last_animation == &right) curr_animation = &downright;
			else if (last_animation == &upright) curr_animation = &right;
			else if (last_animation == &upleft) curr_animation = &left;
			else if (last_animation == &up) curr_animation = &upleft;
			else curr_animation = &down;
			position.y += speed;
			break;
		case LEFT:
			if (last_animation == &up) curr_animation = &upleft;
			else if (last_animation == &right) curr_animation = &upright;
			else if (last_animation == &downright) curr_animation = &down;
			else if (last_animation == &upright) curr_animation = &up;
			else if (last_animation == &down) curr_animation = &downleft;
			else curr_animation = &left;
			position.x -= speed;
			break;
		case RIGHT:
			if (last_animation == &up) curr_animation = &upright;
			else if (last_animation == &left) curr_animation = &upleft;
			else if (last_animation == &downleft) curr_animation = &down;
			else if (last_animation == &upleft) curr_animation = &up;
			else if (last_animation == &down) curr_animation = &downright;
			else curr_animation = &right;
			position.x += speed;
			break;
		case UP_LEFT:
			if (last_animation == &upright) curr_animation = &up;
			else if (last_animation == &downleft) curr_animation = &left;
			else if (last_animation == &right) curr_animation = &upright;
			else if (last_animation == &downright) curr_animation = &right;
			else if (last_animation == &down) curr_animation = &downleft;
			else curr_animation = &upleft;
			break;
		case UP_RIGHT:
			if (last_animation == &upleft) curr_animation = &up;
			else if (last_animation == &downleft) curr_animation = &down;
			else if (last_animation == &left) curr_animation = &downleft;
			else if (last_animation == &downright) curr_animation = &right;
			else if (last_animation == &down) curr_animation = &downright;
			else curr_animation = &upright;
			break;
		case DOWN_LEFT:
			if (last_animation == &upleft) curr_animation = &left;
			else if (last_animation == &upright) curr_animation = &up;
			else if (last_animation == &right) curr_animation = &downright;
			else if (last_animation == &downright) curr_animation = &down;
			else if (last_animation == &up) curr_animation = &upleft;
			else curr_animation = &downleft;
			break;
		case DOWN_RIGHT:
			if (last_animation == &upright) curr_animation = &right;
			else if (last_animation == &downleft) curr_animation = &down;
			else if (last_animation == &left) curr_animation = &downleft;
			else if (last_animation == &upleft) curr_animation = &left;
			else if (last_animation == &up) curr_animation = &upright;
			else curr_animation = &downright;
			break;
		}
		break;
	case true:
		switch (direction)
		{
		case UP:
			curr_animation = &up2;
			position.y -= speed;
			break;
		case DOWN:
			curr_animation = &down2;
			position.y += speed;
			break;
		case LEFT:
			curr_animation = &left2;
			position.x -= speed;
			break;
		case RIGHT:
			curr_animation = &right2;
			position.x += speed;
			break;
		}
		break;
	}
}

		

void ModulePlayer::Fire(Directions dir)
{
	switch (dir)
	{
	case UP:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);
					
				App->particles->AddParticle(App->particles->laserup, position.x + 20, position.y - 10, { 0, -7 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionup, position.x + 14, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67_2, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112_2, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserup2, position.x + 17, position.y - 12, { 0, -7 }, { 0, 0, 10, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionup, position.x + 14, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y - 15, { 0, -7 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionup, position.x + 14, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		else
		{
			if (laser == 1)
			{
				App->particles->AddParticle(App->particles->triple1r, position.x + 23, position.y - 12, { +4, -7 }, { 0, 0, 10, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple1c, position.x + 12, position.y - 12, { 0, -7 }, { 0, 0, 6, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple1l, position.x - 2, position.y - 12, { -4, -7 }, { 0, 0, 10, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple_exp, position.x - 3, position.y - 12, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				App->particles->AddParticle(App->particles->triple2r, position.x + 23, position.y - 12, { +4, -7 }, { 0, 0, 12, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple2c, position.x + 12, position.y - 12, { 0, -7 }, { 0, 0, 9, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple2l, position.x - 2, position.y - 12, { -4, -7 }, { 0, 0, 12, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple_exp, position.x - 3, position.y - 12, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				App->particles->AddParticle(App->particles->triple3r, position.x + 23, position.y - 12, { +4, -7 }, { 0, 0, 15, 21 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple3c, position.x + 12, position.y - 12, { 0, -7 }, { 0, 0, 13, 21 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple3l, position.x - 2, position.y - 12, { -4, -7 }, { 0, 0, 15, 21 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->triple_exp, position.x - 3, position.y - 12, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case DOWN:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserup, position.x + 5, position.y + 19, { 0, +7 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondown, position.x - 1, position.y + 28, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112_2, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67_2, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserup2, position.x + 2, position.y + 25, { 0, +7 }, { 0, 0, 10, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondown, position.x - 1, position.y + 28, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x - 5, position.y + 13, { 0, +7 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondown, position.x - 1, position.y + 28, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case LEFT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 17, 12 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserright, position.x - 8, position.y + 5, { -7, 0 }, { 0, 0, 18, 5 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionleft, position.x - 15, position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157_2, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22_2, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 17, 12 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserright2, position.x - 7, position.y + 2, { -7, 0 }, { 0, 0, 18, 10 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionleft, position.x - 15, position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &upleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downleft && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x - 16, position.y - 5, { -7, 0 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionleft, position.x - 15, position.y, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case RIGHT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22, position.x + 29, position.y, { 7, -4 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserright, position.x + 29, position.y + 10, { +7, 0 }, { 0, 0, 18, 5 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionright, position.x + 29, position.y + 4, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22_2, position.x + 29, position.y, { 7, -4 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157_2, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserright2, position.x + 29, position.y + 7, { +7, 0 }, { 0, 0, 18, 10 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionright, position.x + 29, position.y + 4, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &upright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 29, position.y, { 7, -4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &downright && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x + 29, position.y, { +7, 0 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionright, position.x + 29, position.y + 4, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case UP_LEFT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupleft, position.x + 5, position.y - 10, { -6, -6 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupleft, position.x, position.y - 14, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112_2, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157_2, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupleft2, position.x + 5, position.y - 10, { -6, -6 }, { 0, 0, 18, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupleft, position.x, position.y - 14, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y - 8, { -4, -7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 2, position.y - 2, { -7, -4 }, { 0, 0, 24, 24}, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x - 5, position.y - 18, { -6, -6 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupleft, position.x, position.y - 14, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case UP_RIGHT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22, position.x + 29, position.y, { 7, -4 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupright, position.x + 20, position.y - 10, { +6, -6 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupright, position.x + 20, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67_2, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22_2, position.x + 29, position.y, { 7, -4 }, { 0, 0, 5, 18 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupright2, position.x + 20, position.y - 10, { +6, -6 }, { 0, 0, 18, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupright, position.x + 20, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &up && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 15, position.y - 8, { 4, -7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 29, position.y, { 7, -4 }, { 0, 0, 24, 24}, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x + 15, position.y - 15, { +6, -6 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosionupright, position.x + 20, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case DOWN_LEFT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 17, 12 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupright, position.x - 11, position.y + 12, { -6, +6 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownleft, position.x - 11, position.y + 16, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser22_2, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 17, 12 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser67_2, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 11, 17 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupright2, position.x - 9, position.y + 12, { -6, +6 }, { 0, 0, 18, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownleft, position.x - 11, position.y + 16, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &left && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x - 7, position.y + 7, { -7, 4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x - 10, position.y + 19, { -4, +7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x - 16, position.y + 12, { -6, +6 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownleft, position.x - 11, position.y + 16, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	case DOWN_RIGHT:
		if (weapon == false)
		{
			if (laser == 1)
			{
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupleft, position.x + 12, position.y + 12, { +6, +6 }, { 0, 0, 14, 14 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownright, position.x + 17, position.y + 20, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 2)
			{
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser157_2, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 16, 10 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser112_2, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 11, 16 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laserupleft2, position.x + 10, position.y + 13, { +6, +6 }, { 0, 0, 18, 18 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownright, position.x + 17, position.y + 20, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
			if (laser == 3)
			{
				if (last_animation == &right && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 23, position.y + 15, { 7, 4 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);
				if (last_animation == &down && direction != IDLE)
					App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y + 19, { 4, +7 }, { 0, 0, 24, 24 }, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y + 13, { +6, +6 }, { 0, 0, 23, 23 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->explosiondownright, position.x + 17, position.y + 20, { 0, 0 }, nullrect, COLLIDER_NONE);
			}
		}
		break;
	}

	last_laser = SDL_GetTicks();
	App->audio->PlayFX(basic_laser);
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (self == c1 && self != nullptr && self->type != COLLIDER_EXPLOSION && (c2->type == COLLIDER_WALL || c2->type == COLLIDER_TURRET || c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_TURRET_WALL))
	{
		if (position.y + 4 >= c2->rect.y + c2->rect.h)
		{
			position.y = c2->rect.y + c2->rect.h;
		}

		else if (position.y + c1->rect.h - 4 <= c2->rect.y)
		{
			position.y = c2->rect.y - c1->rect.h;
		}

		else if (position.x <= c2->rect.x + c2->rect.w)
		{
			position.x = last_position.x;
		}

		else if (c1->rect.x + c1->rect.w <= c2->rect.x)
		{
			position.x = last_position.x;
		}
	}

	if (self == c1 && self != nullptr && self->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT && !destroyed)
	{
		App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
		destroyed = true;
		Disable();
		lives--;
	}
}