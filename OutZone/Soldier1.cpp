#include "Application.h"
#include "Soldier1.h"
#include "ModuleCollision.h"
#include "Path.h"
#include"p2Point.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

Soldier1::Soldier1(int x, int y) :Enemy(x, y)
{
	//TURRET SPRITES!!!!!!!!
	//TURRET SPRITES!!!!!!!!
	//TURRET SPRITES!!!!!!!!
	//TURRET SPRITES!!!!!!!!
	//TURRET SPRITES!!!!!!!!
	walk.PushBack({ 11, 6, 27, 31 }); // UP
	walk.PushBack({ 11, 45, 28, 27 }); // RIGHT
	walk.PushBack({ 9, 117, 30, 27 }); // LEFT
	walk.PushBack({ 9, 80, 29, 29 }); // DOWN
	
	walk.PushBack({ 74, 8, 27, 29 }); // UP_RIGHT
	walk.PushBack({ 76, 114, 23, 29 }); // UP_LEFT
	walk.PushBack({ 74, 44, 28, 28 }); // DOWN_RIGHT
	walk.PushBack({ 76, 80, 26, 28 }); //DOWN_LEFT
	
	walk.PushBack({ 43, 116, 28, 27 }); // LEFT_M_UP
	walk.PushBack({ 109, 113, 23, 30 }); // LEFT_U_UP
	walk.PushBack({ 106, 10, 27, 27 }); // RIGHT_M_UP 
	walk.PushBack({ 43, 7, 26, 30 }); // RIGHT_U_UP

	walk.PushBack({ 106, 43, 28, 29 }); // RIGHT_B_BOT
	walk.PushBack({ 43, 44, 27, 28 }); // RIGHT_M_BOT
	walk.PushBack({ 106, 80, 29, 28 }); // LEFT_M_BOT
	walk.PushBack({ 43, 80, 27, 29 }); // LEFT_B_BOT

	walk.speed = 0.5f;

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	path.PushBack({ -0.8f, 0.1f }, 150, &walk);
	path.PushBack({ 0.8f, 0.1f }, 150, &walk);
	//Set the automathic paths here
	
	original_pos.x = x;
	original_pos.y = y;

}

void Soldier1::Move()
{

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
		walk.setframe(RIGHT);
		direction = RIGHT;

	}
	else if (dx > 0 && dy > 0 && angle>11.25 && angle < 33.75)
	{
		walk.setframe(RIGHT_M_BOT);
		direction = RIGHT_M_BOT;

	}
	else if (dx > 0 && dy > 0 && angle>33.75 && angle < 56.25)
	{
		walk.setframe(DOWN_RIGHT);
		direction = DOWN_RIGHT;

	}
	else if (dx > 0 && dy > 0 && angle>56.25 && angle < 78.25)
	{
		walk.setframe(RIGHT_B_BOT);
		direction = RIGHT_B_BOT;
	}
	else if (dx > 0 && dy > 0 && angle>78.25 && angle < 90)
	{
		walk.setframe(DOWN);
		direction = DOWN;
	}
	//bot left quadrant
	else if (dx < 0 && (angle>168.75))
	{
		walk.setframe(LEFT);
		direction = LEFT;

	}
	else if (dx < 0 && dy>0 && angle<168.75 && angle>146.25)
	{
		walk.setframe(LEFT_M_DOWN);
		direction = LEFT_M_DOWN;

	}
	else if (dx < 0 && (angle<146.25) && (angle>123.75))
	{
		walk.setframe(DOWN_LEFT);
		direction = DOWN_LEFT;

	}
	else if (dx < 0 && dy>0 && angle < 123.75 && angle >101.75)
	{
		walk.setframe(LEFT_B_DOWN);
		direction = LEFT_B_DOWN;
	}
	else if (dx < 0 && dy>0 && angle<101.75 && angle > 90)
	{
		walk.setframe(DOWN);
		direction = DOWN;
	}

	//top left quadrant
	else if (dx > 0 && angle>0 && angle<11.25)
	{
		walk.setframe(LEFT);
		direction = LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>-168.75 && angle < -146.25)
	{
		walk.setframe(LEFT_M_UP);
		direction = LEFT_M_UP;
	}
	else if (dx < 0 && dy < 0 && angle>-146.25 && angle < -123.75)
	{
		walk.setframe(UP_LEFT);
		direction = UP_LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>-123.75 && angle < -101.75)
	{
		walk.setframe(LEFT_U_UP);
		direction = LEFT_U_UP;
	}
	else if (dx < 0 && dy < 0 && angle>-101.75 && angle < -90)
	{
		walk.setframe(UP);
		direction = UP;
	}
	//top right quadrant
	else if (dx>0 && dy<0 && angle<-0.1 && angle>-11.25)
	{
		walk.setframe(RIGHT);
		direction = RIGHT;
	}
	else if (dx>0 && dy<0 && angle < -11.25 && angle > -33.75)
	{
		walk.setframe(RIGHT_M_UP);
		direction = RIGHT_M_UP;
	}
	else if (dx>0 && dy<0 && angle < -33.75 && angle > -56.25)
	{
		walk.setframe(UP_RIGHT);
		direction = UP_RIGHT;
	}
	else if (dx>0 && dy<0 && angle < -56.25 && angle > -78.25)
	{
		walk.setframe(RIGHT_U_UP);
		direction = RIGHT_U_UP;
	}
	else if (dx>0 && dy<0 && angle < -78.25 && angle > -89.1)
	{
		walk.setframe(UP);
		direction = UP;
	}

	// Move with the path
	position = original_pos + path.GetCurrentSpeed();


}

void Soldier1::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 1800 && distance>100 && distance <350)
	{
		switch (direction)
		{
		case UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 9, position.y - 6, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 5, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 10, position.y + 19, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 5, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 5, position.y + 6, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 10, position.y + 1, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 25, position.y + 6, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 20, position.y + 1, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case UP_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 5, position.y - 5, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 10, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case UP_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 22, position.y - 5, { +2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 18, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case DOWN_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 5, position.y + 20, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 10, position.y + 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case DOWN_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 23, position.y + 20, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 18, position.y + 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case LEFT_M_DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 5, position.y + 14, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 10, position.y + 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case LEFT_B_DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 1, position.y + 22, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 5, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case LEFT_M_UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 5, position.y - 4, { -2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 10, position.y - 8, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case LEFT_U_UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 1, position.y - 4, { -1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x - 5, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case RIGHT_M_BOT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 25, position.y + 14, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 20, position.y + 10, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case RIGHT_B_BOT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 17, position.y + 22, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 12, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case RIGHT_M_UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 25, position.y - 4, { +2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 20, position.y - 8, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;
		case RIGHT_U_UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 17, position.y - 4, { +1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->explosionshot, position.x + 12, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
			break;

		}
		last_shoot = SDL_GetTicks();
	}

}


void Soldier1::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &walk.GetActualFrame(), -1.0f);

}