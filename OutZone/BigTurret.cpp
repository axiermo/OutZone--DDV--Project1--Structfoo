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
	anim.PushBack({ 22,781,63,64}); // UP

	animation = &anim;

	collider = App->collision->AddCollider({ 0, 0, 63,64 }, COLLIDER_TURRET, App->enemies);

	position.x = x;
	position.y = y;

	lives = 20;

	last_shoot = SDL_GetTicks();
	//TODO change the sprite to the hole in the ground
	
	if (x < 100)
	{
		left = true;
		direction = RIGHT_B_BOT;
		previous = DOWN_RIGHT;
	}
	else
	{
		left = false;
		direction = LEFT_B_DOWN;
		previous = DOWN_LEFT;
	}

}


void BigTurret::Move()
{
	if (left)
	{
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == RIGHT_B_BOT)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_RIGHT;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == DOWN_RIGHT)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = RIGHT_M_BOT;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == RIGHT_M_BOT)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_RIGHT2;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == DOWN_RIGHT2)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
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
				App->particles->AddParticle(App->particles->basic_bullet, position.x - 12, position.y + 12, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_LEFT;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == DOWN_LEFT)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x - 12, position.y + 12, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = LEFT_M_DOWN;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == LEFT_M_DOWN)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x - 12, position.y + 12, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_LEFT2;
				last_shoot = SDL_GetTicks();
			}
		}

		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450)
		{
			if (direction == DOWN_LEFT2)
			{
				App->particles->AddParticle(App->particles->basic_bullet, position.x - 12, position.y + 12, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = LEFT_B_DOWN;
				last_shoot = SDL_GetTicks();
			}
		}


	}
}
/*
void BigTurret::Shoot()
{
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 450)
	{
		switch (direction)
		{
		case DOWN_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 11, position.y + 12, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_RIGHT2:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case RIGHT_M_BOT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case RIGHT_B_BOT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case LEFT_M_DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case LEFT_B_DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		}
		last_shoot = SDL_GetTicks();
	}
}
*/


void BigTurret::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(),-1.0f);
}
