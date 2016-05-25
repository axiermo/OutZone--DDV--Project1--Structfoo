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
#include "ModuleFonts.h"
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

	explosion.PushBack({ 241, 0, 115, 110 });
	explosion.PushBack({ 361, 0, 115, 110 });
	explosion.PushBack({ 479, 0, 115, 110 });
	explosion.PushBack({ 596, 0, 115, 110 });
	explosion.PushBack({ 241, 112, 117, 114 });
	explosion.PushBack({ 359, 113, 113, 113 });
	explosion.PushBack({ 476, 113, 113, 113 });
	explosion.PushBack({ 593, 113, 114, 112 });
	explosion.PushBack({ 710, 113, 113, 113 });
	explosion.speed = 0.15f;
	explosion.loop = false;
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
	if (self->type == COLLIDER_PLAYER || self->type == COLLIDER_GOD)
	{
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
		
		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_UP){
			if (App->player->bombs>0){ //<- check if there's bombs available (not implemented)
				App->particles->AddParticle(App->particles->Player_explosion, App->render->camera.x, (-App->render->camera.y * 2 / speed) + 47, { 0, 0 }, { 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Player_explosion, App->render->camera.x, (-App->render->camera.y * 2 / speed) + 129, { 0, 0 }, { 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->Player_explosion, App->render->camera.x, (-App->render->camera.y * 2 / speed) + 235, { 0, 0 }, { 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
				App->player->bombs--;

			}
		}
		
		if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_UP)
			bombs++;

		t0 = SDL_GetTicks();
		if (t0 - t1 > 1600){
			energy--;
			t1 = SDL_GetTicks();
		}

		if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_UP)
			score += 10000;
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
	}

	if (destroyed == true && !explosion.Finished())
	{
		SelectAnimation(direction = EXPLOSION);
		
		if (self->rect.x > position.x - 40 && self->rect.y > position.y - 40)
		{
			self->rect.x -= 2;
			self->rect.y -= 2;
		}
		if (self->rect.w < 115 && self->rect.h < 115)
		{
			self->rect.w += 3.5;
			self->rect.h += 3.5;
		}
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

	if (direction == EXPLOSION)
		App->render->Blit(graphics, position.x - 40, position.y - 40, &(curr_animation->GetCurrentFrame()), -1.0f);
	else if (direction != IDLE)
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetCurrentFrame()),-1.0f);
	else
		App->render->Blit(graphics, position.x, position.y, &(curr_animation->GetActualFrame()),-1.0f);

	// MODIFY COLLISION -------------------------------------------------

	if (direction != EXPLOSION)
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
	case EXPLOSION:
		curr_animation = &explosion;
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

	if (self == c1 && self != nullptr && self->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		destroyed = true;
		int x = App->player->position.x + 10;
		int y = App->player->position.y + 10;

		self->rect.x = x;
		self->rect.y = y;
		self->rect.w = 10;
		self->rect.h = 10;
		self->type = COLLIDER_EXPLOSION;
	}
}
	