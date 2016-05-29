#include "Application.h"
#include "GreyTurret.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

GreyTurret::GreyTurret(int x, int y) : Enemy(x, y,0)
{
	rotate.PushBack({ 11, 6, 27, 31 }); // UP
	rotate.PushBack({ 11, 45, 28, 27 }); // RIGHT
	rotate.PushBack({ 9, 117, 30, 27 }); // LEFT
	rotate.PushBack({ 9, 80, 29, 29 }); // DOWN
	rotate.PushBack({ 74, 8, 27, 29 }); // UP_RIGHT
	rotate.PushBack({ 76, 114, 23, 29 }); // UP_LEFT
	rotate.PushBack({ 74, 44, 28, 28 }); // DOWN_RIGHT
	rotate.PushBack({ 76, 80, 26, 28 }); //DOWN_LEFT
	rotate.PushBack({ 43, 116, 28, 27 }); // LEFT_M_UP
	rotate.PushBack({ 109, 113, 23, 30 }); // LEFT_U_UP
	rotate.PushBack({ 106, 10, 27, 27 }); // RIGHT_M_UP 
	rotate.PushBack({ 43, 7, 26, 30 }); // RIGHT_U_UP
	rotate.PushBack({ 106, 43, 28, 29 }); // RIGHT_B_BOT
	rotate.PushBack({ 43, 44, 27, 28 }); // RIGHT_M_BOT
	rotate.PushBack({ 106, 80, 29, 28 }); // LEFT_M_BOT
	rotate.PushBack({ 43, 80, 27, 29 }); // LEFT_B_BOT
	rotate.PushBack({ 43, 80, 27, 29 }); // LEFT_B_BOT
	rotate.PushBack({ 43, 80, 27, 29 }); // LEFT_B_BOT
	rotate.PushBack({ 98, 868, 37, 37 }); // DEAD

	lives = 4;

	animation = &rotate;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TURRET, App->enemies);

	position.x = x;
	position.y = y;

	last_shoot = SDL_GetTicks();
	direction = DOWN;
}


void GreyTurret::Move()
{
	//while !insiderange
	//define the animation of the turret
	float angle, dx, dy;
	int player_position_x, player_position_y;

	player_position_x = App->player->position.x;

	player_position_y = App->player->position.y;

	dx = float(player_position_x - position.x);

	dy = float(player_position_y - position.y);

	angle = atan2(dy, dx) * 180 / PI;

	//THE ANGLE IS INVERTED    

	//bot right quadrant

	if (dx > 0 && dy > 0 && angle > 0 && angle<11.25)
	{
		rotate.setframe(RIGHT);
		direction = RIGHT;

	}
	else if (dx > 0 && dy > 0 && angle>11.25 && angle < 33.75)
	{
		rotate.setframe(RIGHT_M_BOT);
		direction = RIGHT_M_BOT;

	}
	else if (dx > 0 && dy > 0 && angle>33.75 && angle < 56.25)
	{
		rotate.setframe(DOWN_RIGHT);
		direction = DOWN_RIGHT;

	}
	else if (dx > 0 && dy > 0 && angle>56.25 && angle < 78.25)
	{
		rotate.setframe(RIGHT_B_BOT);
		direction = RIGHT_B_BOT;
	}
	else if (dx > 0 && dy > 0 && angle>78.25 && angle < 90)
	{
		rotate.setframe(DOWN);
		direction = DOWN;
	}
	//bot left quadrant
	else if (dx < 0 && (angle>168.75))
	{
		rotate.setframe(LEFT);
		direction = LEFT;

	}
	else if (dx < 0 && dy>0 && angle<168.75 && angle>146.25)
	{
		rotate.setframe(LEFT_M_DOWN);
		direction = LEFT_M_DOWN;

	}
	else if (dx < 0 && (angle<146.25) && (angle>123.75))
	{
		rotate.setframe(DOWN_LEFT);
		direction = DOWN_LEFT;

	}
	else if (dx < 0 && dy>0 && angle < 123.75 && angle >101.75)
	{
		rotate.setframe(LEFT_B_DOWN);
		direction = LEFT_B_DOWN;
	}
	else if (dx < 0 && dy>0 && angle<101.75 && angle > 90)
	{
		rotate.setframe(DOWN);
		direction = DOWN;
	}

	//top left quadrant
	else if (dx > 0 && angle>0 && angle<11.25)
	{
		rotate.setframe(LEFT);
		direction = LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>-168.75 && angle < -146.25)
	{
		rotate.setframe(LEFT_M_UP);
		direction = LEFT_M_UP;
	}
	else if (dx < 0 && dy < 0 && angle>-146.25 && angle < -123.75)
	{
		rotate.setframe(UP_LEFT);
		direction = UP_LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>-123.75 && angle < -101.75)
	{
		rotate.setframe(LEFT_U_UP);
		direction = LEFT_U_UP;
	}
	else if (dx < 0 && dy < 0 && angle>-101.75 && angle < -90)
	{
		rotate.setframe(UP);
		direction = UP;
	}
	//top right quadrant
	else if (dx>0 && dy<0 && angle<-0.1 && angle>-11.25)
	{
		rotate.setframe(RIGHT);
		direction = RIGHT;
	}
	else if (dx>0 && dy<0 && angle < -11.25 && angle > -33.75)
	{
		rotate.setframe(RIGHT_M_UP);
		direction = RIGHT_M_UP;
	}
	else if (dx>0 && dy<0 && angle < -33.75 && angle > -56.25)
	{
		rotate.setframe(UP_RIGHT);
		direction = UP_RIGHT;
	}
	else if (dx>0 && dy<0 && angle < -56.25 && angle > -78.25)
	{
		rotate.setframe(RIGHT_U_UP);
		direction = RIGHT_U_UP;
	}
	else if (dx>0 && dy<0 && angle < -78.25 && angle > -89.1)
	{
		rotate.setframe(UP);
		direction = UP;
	}
}

void GreyTurret::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();

	if (App->player->position.y - position.y < 160 || appeared)
	{
		appeared = true;
		if (next_shoot - last_shoot > 1800 && distance > 100 && distance < 350 && !destroyed)
		{
			switch (direction)
			{
			case UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 9, position.y - 6, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 19, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 6, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 1, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 25, position.y + 6, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 20, position.y + 1, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case UP_LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y - 5, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case UP_RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 22, position.y - 5, { +2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 18, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN_LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 20, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN_RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 23, position.y + 20, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 18, position.y + 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_M_DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 14, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 10, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_B_DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 1, position.y + 22, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 5, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_M_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y - 4, { -2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y - 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_U_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 1, position.y - 4, { -1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 5, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_M_BOT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 25, position.y + 14, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 20, position.y + 10, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_B_BOT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 17, position.y + 22, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 12, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_M_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 25, position.y - 4, { +2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 20, position.y - 8, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_U_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 17, position.y - 4, { +1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 12, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			}
			last_shoot = SDL_GetTicks();
		}
	}
}


void GreyTurret::Draw()
{
	if (collider != nullptr && !destroyed)
		collider->SetPos(position.x, position.y);
	else
	{
		collider->type = COLLIDER_DEAD;
		collider->SetPos(position.x - 1, position.y + 14);
	}

	if (!destroyed)
	{
		if (hit == false) App->render->Blit(App->enemies->sprites, position.x, position.y, &rotate.GetActualFrame(), -1.0f);
		else
		{
			App->render->Blit(App->enemies->sprites2, position.x, position.y, &rotate.GetActualFrame(), -1.0f);
			t++;

			if (t == 3)
			{
				hit = false;
				t = 0;
			}
		}
	}
	else
	{
		rotate.setframe(17);
		App->render->Blit(App->enemies->sprites, position.x - 1, position.y + 14, &rotate.GetCurrentFrame(), -1.0f);
	}
}