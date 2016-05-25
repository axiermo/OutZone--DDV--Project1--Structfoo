#include "Application.h"
#include "DoorTurret.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

DoorTurret::DoorTurret(int x, int y) : Enemy(x, y, 0)
{
	anim.PushBack({ 90, 793, 26, 40 }); // UP
	anim.PushBack({ 119, 793, 26, 40 }); // UP

	anim.speed = 0.2f;
	animation = &anim;

	lives = 8;

	collider = App->collision->AddCollider({ 0, 0, 26, 40 }, COLLIDER_ENEMY, App->enemies);

	position.x = x;
	position.y = y;

	last_shoot = SDL_GetTicks();

	direction = LEFT;
}

void DoorTurret::Shoot()
{
	if (!destroyed && (App->player->position.y - position.y < 150 || appeared))
	{
		appeared = true;
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 400 && !destroyed)
		{
			if (direction == LEFT)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_LEFT;
				last_shoot = SDL_GetTicks();
			}
		}
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN_LEFT)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN;
				last_shoot = SDL_GetTicks();
			}
		}
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_RIGHT;
				last_shoot = SDL_GetTicks();
			}
		}
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN_RIGHT)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = RIGHT;
				last_shoot = SDL_GetTicks();
			}
		}
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == RIGHT)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_RIGHT2;
				last_shoot = SDL_GetTicks();
			}
		}
		next_shoot = SDL_GetTicks();
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN_RIGHT2)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN2;
				last_shoot = SDL_GetTicks();
			}
		}
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN2)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = DOWN_LEFT2;
				last_shoot = SDL_GetTicks();
			}
		}
		if (next_shoot - last_shoot > 450 && !destroyed)
		{
			if (direction == DOWN_LEFT2)
			{
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 10, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				direction = LEFT;
				last_shoot = SDL_GetTicks();
			}
		}
	}
}


void DoorTurret::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetCurrentFrame(), -1.0f);
}