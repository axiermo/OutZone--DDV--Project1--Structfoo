#include "Application.h"
#include "Mazurka.h"
#include "ModuleCollision.h"
#include "Path.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include <stdlib.h>
#include <time.h>

#define PI 3.1415926

Mazurka::Mazurka(int x, int y, int subtype) :Enemy(x, y, subtype)
{
	mazurka.PushBack({ 301, 781, 64, 59 });
	mazurka.PushBack({ 367, 781, 62, 58 });
	mazurka.speed = 0.2f;
	mazurka.loop = true;

	hit2.PushBack({ 303, 844, 64, 89 });
	hit2.PushBack({ 369, 844, 62, 89 });
	hit2.PushBack({ 434, 844, 64, 89 });
	hit2.PushBack({ 500, 844, 62, 89 });
	hit2.speed = 0.2f;
	hit2.loop = true;

	dead.PushBack({ 447, 37, 64, 80 });

	animation = &mazurka;

	collider = App->collision->AddCollider({ 0, 0, 60, 58 }, COLLIDER_TYPE::COLLIDER_BIG_TURRET, (Module*)App->enemies);

	switch (subtype){
	case 1:
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 3.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		break;
	case 2:
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 80, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 70, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		break;
	case 3:
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 60, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 150, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 30, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		break;
	case 4:
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 48, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 75, &mazurka);
		path.PushBack({ 0.0f, 3.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 78, &mazurka);
		path.PushBack({ 0.0f, 0.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, -1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		path.PushBack({ 0.0f, 1.5f }, 100, &mazurka);
		path.PushBack({ 0.0f, 0.0f }, 100, &mazurka);
		break;
	}

	lives = 102;

	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

}

void Mazurka::Move()
{
	if (!destroyed)
		position = original_pos + path.GetCurrentSpeed();

}

void Mazurka::Shoot()
{

	float angle, dx, dy;
	int player_position_x, player_position_y;

	player_position_x = App->player->position.x;

	player_position_y = App->player->position.y;

	dx = float(player_position_x - position.x);

	dy = float(player_position_y - position.y);



	angle = atan2(dy, dx) * 180 / PI;

	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();

	if (next_shoot - last_shoot > 1800 && distance <350 && !destroyed)
	{
		if (dx > 0 && dy > 0 && angle > 0 && angle<11.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 23, position.y + 11, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx > 0 && dy > 0 && angle>11.25 && angle < 33.75)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 25, position.y + 17, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx > 0 && dy > 0 && angle>33.75 && angle < 56.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 21, position.y + 21, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx > 0 && dy > 0 && angle>56.25 && angle < 78.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 17, position.y + 22, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx > 0 && dy > 0 && angle>78.25 && angle < 90)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 10, position.y + 22, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		//bot left quadrant
		else if (dx < 0 && (angle>168.75))
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x - 5, position.y + 12, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);

		}
		else if (dx < 0 && dy>0 && angle<168.75 && angle>146.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x - 5, position.y + 17, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && (angle<146.25) && (angle>123.75))
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x - 5, position.y + 23, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy>0 && angle < 123.75 && angle >101.75)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 1, position.y + 22, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy>0 && angle<101.75 && angle > 90)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 10, position.y + 22, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}

		//top left quadrant
		else if (dx > 0 && angle>0 && angle<11.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x - 5, position.y + 12, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy < 0 && angle>-168.75 && angle < -146.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 0, position.y - 5, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy < 0 && angle>-146.25 && angle < -123.75)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 0, position.y - 5, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy < 0 && angle>-123.75 && angle < -101.75)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 5, position.y - 4, { -1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx < 0 && dy < 0 && angle>-101.75 && angle < -90)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 12, position.y - 6, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		//top right quadrant
		else if (dx>0 && dy<0 && angle<-0.1 && angle>-11.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 23, position.y + 11, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx>0 && dy<0 && angle < -11.25 && angle > -33.75)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 21, position.y + 5, { +2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx>0 && dy<0 && angle < -33.75 && angle > -56.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 22, position.y - 2, { +2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx>0 && dy<0 && angle < -56.25 && angle > -78.25)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 17, position.y - 1, { +1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}
		else if (dx>0 && dy<0 && angle < -78.25 && angle > -89.1)
		{
			App->particles->AddParticle(App->particles->Big_Tur_Laser, position.x + 12, position.y - 6, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
		}

		last_shoot = SDL_GetTicks();
	}

}


void Mazurka::Draw()
{
	if (collider != nullptr && !destroyed)
		collider->SetPos(position.x, position.y);
	else
		collider->type = COLLIDER_DEAD;
	 
	if (!destroyed && lives <= 36 && lives > 0)
		App->render->Blit(App->enemies->sprites, position.x, position.y - 30, &hit2.GetCurrentFrame(), -1.0f);
	else if
		(!destroyed && lives > 36) App->render->Blit(App->enemies->sprites, position.x, position.y, &mazurka.GetCurrentFrame(), -1.0f);
	else
		App->render->Blit(App->enemies->sprites, position.x, position.y, &dead.GetCurrentFrame(), -1.0f);

	if (hit == false && !destroyed) App->render->Blit(App->enemies->sprites, position.x, position.y, &(mazurka.GetCurrentFrame()), -1.0f);
	else
	{
		if (!destroyed) App->render->Blit(App->enemies->sprites2, position.x, position.y, &mazurka.GetActualFrame(), -1.0f);
		t++;

		if (t == 5)
		{
			hit = false;
			t = 0;
		}
	}
}