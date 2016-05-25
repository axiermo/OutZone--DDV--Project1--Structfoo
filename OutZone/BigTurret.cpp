#include "Application.h"
#include "BigTurret.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

BigTurret::BigTurret(int x, int y) : Enemy(x, y,0)
{
	animation = &anim;

	collider = App->collision->AddCollider({ 0, 0, 63,64 }, COLLIDER_BIG_TURRET, App->enemies);

	// Dead fire anim
	dead.PushBack({ 42, 1008, 70, 60 });
	dead.PushBack({ 45, 1085, 70, 60 });
	dead.PushBack({ 43, 1243, 70, 60 });
	dead.PushBack({ 42, 940, 70, 60 });
	dead.PushBack({ 45, 1158, 70, 60 });
	dead.speed = 0.2f;

	// Left turret
	hit1_left.PushBack({ 152, 39, 65, 82 });
	hit1_left.PushBack({ 222, 39, 65, 82 });
	hit1_left.PushBack({ 292, 39, 65, 82 });
	hit1_left.PushBack({ 362, 39, 65, 82 });
	hit1_left.speed = 0.5f;

	hit2_left.PushBack({ 152, 291, 65, 82 });
	hit2_left.PushBack({ 222, 291, 65, 82 });
	hit2_left.PushBack({ 292, 291, 65, 82 });
	hit2_left.PushBack({ 362, 291, 65, 82 });
	hit2_left.speed = 0.5f;

	// Right turret
	hit1_right.PushBack({ 152, 416, 65, 82 });
	hit1_right.PushBack({ 222, 416, 65, 82 });
	hit1_right.PushBack({ 292, 416, 65, 82 });
	hit1_right.PushBack({ 362, 416, 65, 82 });
	hit1_right.speed = 0.5f;
		
	hit2_right.PushBack({ 152, 165, 65, 82 });
	hit2_right.PushBack({ 222, 165, 65, 82 });
	hit2_right.PushBack({ 292, 165, 65, 82 });
	hit2_right.PushBack({ 362, 165, 65, 82 });
	hit2_right.speed = 0.5f;

	position.x = x;
	position.y = y;

	lives = 20;

	last_shoot = SDL_GetTicks();

	if (x < 100)
	{
		anim.PushBack({ 22, 781, 63, 64 });
		left = true;
		direction = RIGHT_B_BOT;
	}
	else
	{
		anim.PushBack({ 22, 853, 63, 64 });
		left = false;
		direction = LEFT_B_DOWN;
	}
}


void BigTurret::Shoot()
{
	if (!destroyed && (App->player->position.y - position.y < 165 || appeared))
	{
		appeared = true;
		if (left)
		{
			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == RIGHT_B_BOT)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +1, +2 }, { 0, 0, 12, 12 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 25, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = DOWN_RIGHT;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == DOWN_RIGHT)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +2 }, { 0, 0, 12, 12 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 25, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = RIGHT_M_BOT;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == RIGHT_M_BOT)
				{

					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +1 }, { 0, 0, 12, 12 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 25, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = DOWN_RIGHT2;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == DOWN_RIGHT2)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +2 }, { 0, 0, 12, 12 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 25, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = RIGHT_B_BOT;
					last_shoot = SDL_GetTicks();
				}
			}
		}
		else
		{
			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == LEFT_B_DOWN)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 15, position.y + 45, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 5, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = DOWN_LEFT;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == DOWN_LEFT)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 15, position.y + 45, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 5, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = LEFT_M_DOWN;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == LEFT_M_DOWN)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 15, position.y + 45, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 5, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = DOWN_LEFT2;
					last_shoot = SDL_GetTicks();
				}
			}

			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == DOWN_LEFT2)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 15, position.y + 45, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Big_Tur_Exp, position.x + 5, position.y + 35, { 0, 0 }, nullrect, COLLIDER_NONE);
					direction = LEFT_B_DOWN;
					last_shoot = SDL_GetTicks();
				}
			}
		}
	}
}

void BigTurret::Draw()
{
	if (collider != nullptr && !destroyed)
		collider->SetPos(position.x, position.y);
	else
		collider->type = COLLIDER_DEAD;

	// Drawing correct anim of the turret depending on the damage received.
	if (left)
	{
		if (!destroyed && lives <= 12 && lives > 8)
			App->render->Blit(App->enemies->sprites, position.x - 1, position.y - 15, &hit1_left.GetCurrentFrame(), -1.0f);
		else if
			(!destroyed && lives <= 8 && lives > 0) App->render->Blit(App->enemies->sprites, position.x - 1, position.y - 16, &hit2_left.GetCurrentFrame(), -1.0f);
		else if
			(!destroyed && lives > 12) App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(), -1.0f);
		else
			App->render->Blit(App->enemies->sprites, position.x - 10, position.y, &dead.GetCurrentFrame(), -1.0f);
	}
	else
	{
		if (!destroyed && lives <= 12 && lives > 8)
			App->render->Blit(App->enemies->sprites, position.x - 1, position.y - 17, &hit1_right.GetCurrentFrame(), -1.0f);
		else if
			(!destroyed && lives <= 8 && lives > 0) App->render->Blit(App->enemies->sprites, position.x - 1, position.y - 15, &hit2_right.GetCurrentFrame(), -1.0f);
		else if
			(!destroyed && lives > 12) App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(), -1.0f);
		else
			App->render->Blit(App->enemies->sprites, position.x - 10, position.y, &dead.GetCurrentFrame(), -1.0f);
	}
}
