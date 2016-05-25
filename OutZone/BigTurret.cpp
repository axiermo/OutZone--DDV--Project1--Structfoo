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

	dead.PushBack({ 19, 945, 74, 82 });
	dead.PushBack({ 23, 1066, 78, 82 });
	dead.PushBack({ 29, 1179, 78, 82 });
	dead.PushBack({ 33, 1290, 76, 82 });
	dead.PushBack({ 34, 1400, 84, 82 });
	dead.speed = 0.15f;

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
	if (!destroyed)
	{
		if (left)
		{
			next_shoot = SDL_GetTicks();
			if (next_shoot - last_shoot > 450)
			{
				if (direction == RIGHT_B_BOT)
				{
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
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
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
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

					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
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
					App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 30, position.y + 40, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
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

	if (!destroyed) App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(), -1.0f);
	else
		App->render->Blit(App->enemies->sprites, position.x - 10, position.y - 20, &dead.GetCurrentFrame(), -1.0f);
}
