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
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"
#define PI 3.1415926

Soldier1::Soldier1(int x, int y, int subtype) :Enemy(x, y, subtype)
{
	up.PushBack({ 14, 162, 26, 36 });
	up.PushBack({ 46, 161, 27, 37 });
	up.PushBack({ 79, 162, 26, 35 });
	up.PushBack({ 110, 161, 26, 35 });
	up.speed = 0.1f;

	right.PushBack({ 13, 243, 28, 32 });
	right.PushBack({ 48, 242, 25, 32 });
	right.PushBack({ 78, 243, 27, 32 });
	right.PushBack({ 112, 242, 25, 33 });
	right.speed = 0.1f;

	left.PushBack({ 76, 403, 25, 33 });
	left.PushBack({ 108, 402, 25, 32 });
	left.PushBack({ 12, 401, 28, 34 });
	left.PushBack({ 44, 402, 25, 33 });
	left.speed = 0.1f;

	down.PushBack({ 10, 323, 27, 35 });
	down.PushBack({ 43, 323, 27, 32 });
	down.PushBack({ 75, 324, 28, 33 });
	down.PushBack({ 107, 323, 27, 31 });
	down.speed = 0.1f;

	upleft.PushBack({ 108, 441, 28, 33 });
	upleft.PushBack({ 76, 443, 28, 34 });
	upleft.PushBack({ 44, 441, 28, 35 });
	upleft.PushBack({ 14, 442, 26, 35 });
	upleft.speed = 0.1f;

	downleft.PushBack({ 12, 363, 27, 33 });
	downleft.PushBack({ 44, 362, 27, 34 });
	downleft.PushBack({ 76, 363, 25, 34 });
	downleft.PushBack({ 108, 362, 27, 34 });
	downleft.speed = 0.1f;

	downright.PushBack({ 11, 283, 27, 34 });
	downright.PushBack({ 43, 282, 26, 33 });
	downright.PushBack({ 75, 283, 27, 33 });
	downright.PushBack({ 107, 282, 26, 35 });
	downright.speed = 0.1f;

	upright.PushBack({ 12, 203, 29, 34 });
	upright.PushBack({ 47, 202, 26, 34 });
	upright.PushBack({ 81, 203, 24, 33 });
	upright.PushBack({ 112, 202, 25, 36 });
	upright.speed = 0.1f;

	curr_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	switch (subtype)
	{
	case 1:
		path.PushBack({ 0.0f, 0.9f }, 50, &down);
		path.PushBack({ 0.5f, 0.8f }, 150, &downright);
		path.PushBack({ 0.7f, 0.3f }, 150, &downright);
		path.PushBack({ 0.9f, 0.1f }, 150, &downright);
		break;
	case 2:
		path.PushBack({ 0.0f, 1.0f }, 150, &down);
		break;
	case 3:
		path.PushBack({ 0.0f, 0.0f }, 150, &walk);
		break;
	case 4:

		path.PushBack({ -0.3f, 0.7f }, 60, &downleft);
		path.PushBack({ 0.0f, 0.0f }, 60, &walk);
		path.PushBack({ -0.5f, 0.8f }, 100, &downleft);
		path.PushBack({ -0.7f, 0.8f }, 150, &downleft);
		break;
	case 5://!!!
		path.PushBack({ 0.7f, 0.0f }, 115, &right);
		path.PushBack({ 0.0f, 0.0f }, 20, &walk);
		path.PushBack({ -0.7f, 0.0f }, 115, &left);
		path.PushBack({ 0.0f, 0.0f }, 20, &walk);
		break;
	case 6:
		path.PushBack({ -1.0f, 0.0f }, 120, &left);
		path.PushBack({ -0.8f, 0.4f }, 40, &upleft);
		path.PushBack({ -0.8f, -0.4f }, 80, &downleft);
		path.PushBack({ -0.8f, 0.4f }, 40, &upleft);
		path.PushBack({ -0.8f, 0.0f }, 150, &left);
		break;
	case 7:
		path.PushBack({ -0.8f, 0.0f }, 150, &left);
		path.PushBack({ -0.8f, 0.0f }, 40, &left);
		path.PushBack({ 0.0f, 0.4f }, 80, &up);
		break;
	case 8:
		path.PushBack({ -0.8f, 0.0f }, 150, &left);
		path.PushBack({ 0.8f, 0.0f }, 40, &right);
		path.PushBack({ -0.8f, -0.4f }, 80, &upleft);
		break;
	case 9:
		path.PushBack({ 0.0f, -0.9f }, 20, &up);
		path.PushBack({ 0.8f, 0.0f }, 40, &right);
		break;
	case 10:
		path.PushBack({ -0.3f, 0.5f }, 60, &downleft);
		path.PushBack({ -0.5f, 0.4f }, 100, &downleft);
		path.PushBack({ -0.7f, 0.2f }, 150, &downleft);
		path.PushBack({ -0.9f, 0.1f }, 150, &downleft);
	case 11:
		path.PushBack({ 0.0f, 0.9f }, 130, &down);
		path.PushBack({ 0.5f, 0.8f }, 150, &downright);
		path.PushBack({ 0.7f, 0.3f }, 150, &downright);
		path.PushBack({ 0.9f, 0.1f }, 150, &downright);
		break;
	case 12://!!!
		path.PushBack({ 0.75f, 0.0f }, 95, &right);
		path.PushBack({ 0.0f, 0.0f }, 10, &walk);
		path.PushBack({ -0.75f, 0.0f }, 95, &left);
		path.PushBack({ 0.0f, 0.0f }, 10, &walk);
		break;
	case 13://!!!
		path.PushBack({ 0.68f, 0.0f }, 75, &left);
		path.PushBack({ 0.0f, 0.0f }, 10, &walk);
		path.PushBack({ -0.68f, 0.0f }, 75, &left);
		path.PushBack({ 0.0f, 0.0f }, 10, &walk);
		break;
	case 14:
		path.PushBack({ 0.0f, 0.9f }, 50, &down);
		path.PushBack({ 0.5f, 0.8f }, 20, &downright);
		path.PushBack({ 0.8f, 0.0f }, 300, &right);
		break;
	case 15:
		path.PushBack({ 0.0f, 0.9f }, 150, &down);
		path.PushBack({ 0.5f, 0.8f }, 20, &right);
		path.PushBack({ 0.8f, 0.0f }, 300, &right);
		break;
	case 16:
		path.PushBack({ -0.6f, 0.0f }, 80, &left);
		path.PushBack({ 0.6f, 0.0f }, 80, &right);
		break;
	case 17:
		path.PushBack({ 0.0f, 0.5f }, 40, &down);
		path.PushBack({ 0.6f, 0.5f }, 40, &downright);
		path.PushBack({ 0.f, 1.0f }, 20, &down);
		path.PushBack({ -0.6f, 0.5f }, 200, &walk);
		break;
	case 18:
		path.PushBack({ 0.0f, 0.5f }, 40, &down);
		path.PushBack({ -0.5f, 0.4f }, 40, &downleft);
		path.PushBack({ -0.5f, 0.8f }, 40, &downleft);
		path.PushBack({ 0.0f, 1.0f }, 20, &down);
		path.PushBack({ 0.5f, 0.2f }, 60, &downright);
		path.PushBack({ 0.7f, 0.0f }, 2000, &right);
		break;
	case 19:
		path.PushBack({ 0.0f, 0.5f }, 40, &down);
		path.PushBack({ -0.3f, 0.8f }, 40, &downleft);
		path.PushBack({ -0.5f, 0.5f }, 60, &downleft);
		path.PushBack({ -0.5f, 0.8f }, 60, &downleft);
		path.PushBack({ 0.0f, 1.0f }, 20, &down);
		path.PushBack({ 0.5f, 0.2f }, 60, &downright);
		path.PushBack({ 0.7f, 0.0f }, 2000, &right);
		break;
	case 20:
		path.PushBack({ 0.0f, 0.5f }, 40, &right);
		path.PushBack({ 0.4f, 0.8f }, 60, &downright);
		path.PushBack({ 0.0f, 1.0f }, 3000, &down);
		break;
	case 21:
		path.PushBack({ 0.0f, 1.0f }, 3000, &down);
		break;

	}

	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

}



void Soldier1::SelectAnimation(Directions direction)
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
void Soldier1::Move()
{
	if (subtype == 21){
		if (App->player->position.x < 120)
			AI.x -= 0.3f;
		else
			AI.x += 0.3f;
	}


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
		direction = RIGHT;
		SelectAnimation(direction);

	}
	else if (dx > 0 && dy > 0 && angle>11.25 && angle < 33.75)
	{
		direction = RIGHT_M_BOT;
		SelectAnimation(direction);

	}
	else if (dx > 0 && dy > 0 && angle>33.75 && angle < 56.25)
	{
		direction = DOWN_RIGHT;
		SelectAnimation(direction);

	}
	else if (dx > 0 && dy > 0 && angle>56.25 && angle < 78.25)
	{
		direction = RIGHT_B_BOT;
		SelectAnimation(direction);
	}
	else if (dx > 0 && dy > 0 && angle>78.25 && angle < 90)
	{
		direction = DOWN;
		SelectAnimation(direction);
	}
	//bot left quadrant
	else if (dx < 0 && (angle>168.75))
	{
		direction = LEFT;
		SelectAnimation(direction);

	}
	else if (dx < 0 && dy>0 && angle<168.75 && angle>146.25)
	{
		direction = LEFT_M_DOWN;
		SelectAnimation(direction);

	}
	else if (dx < 0 && (angle<146.25) && (angle>123.75))
	{
		direction = DOWN_LEFT;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy>0 && angle < 123.75 && angle >101.75)
	{
		direction = LEFT_B_DOWN;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy>0 && angle<101.75 && angle > 90)
	{
		direction = DOWN;
		SelectAnimation(direction);
	}

	//top left quadrant
	else if (dx > 0 && angle>0 && angle<11.25)
	{
		direction = LEFT;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy < 0 && angle>-168.75 && angle < -146.25)
	{
		direction = LEFT_M_UP;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy < 0 && angle>-146.25 && angle < -123.75)
	{
		direction = UP_LEFT;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy < 0 && angle>-123.75 && angle < -101.75)
	{
		direction = LEFT_U_UP;
		SelectAnimation(direction);
	}
	else if (dx < 0 && dy < 0 && angle>-101.75 && angle < -90)
	{
		direction = UP;
		SelectAnimation(direction);
	}
	//top right quadrant
	else if (dx>0 && dy<0 && angle<-0.1 && angle>-11.25)
	{
		direction = RIGHT;
		SelectAnimation(direction);
	}
	else if (dx>0 && dy<0 && angle < -11.25 && angle > -33.75)
	{
		direction = RIGHT_M_UP;
		SelectAnimation(direction);
	}
	else if (dx>0 && dy<0 && angle < -33.75 && angle > -56.25)
	{
		direction = UP_RIGHT;
		SelectAnimation(direction);
	}
	else if (dx>0 && dy<0 && angle < -56.25 && angle > -78.25)
	{
		direction = RIGHT_U_UP;
		SelectAnimation(direction);
	}
	else if (dx>0 && dy<0 && angle < -78.25 && angle > -89.1)
	{
		direction = UP;
		SelectAnimation(direction);
	}

	// Move with the path
	position = original_pos + path.GetCurrentSpeed() + AI;


}

void Soldier1::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();

	if (App->player->position.y - position.y < 120 || appeared)
	{
		appeared = true;
		if (next_shoot - last_shoot > 1800 && distance > 100 && distance < 350)
		{
			switch (direction)
			{
				//GreySoldier correct shot
			case UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 12, position.y - 6, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 7, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 10, position.y + 22, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 5, position.y + 22, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 12, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 7, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 23, position.y + 11, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 18, position.y + 6, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case UP_LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 0, position.y - 5, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 5, position.y - 10, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case UP_RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 22, position.y - 2, { +2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 18, position.y - 7, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN_LEFT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 23, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 18, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case DOWN_RIGHT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 21, position.y + 21, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 16, position.y + 16, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_M_DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 5, position.y + 17, { -2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 10, position.y + 13, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_B_DOWN:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 1, position.y + 22, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 5, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_M_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x - 3, position.y - 1, { -2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 8, position.y - 5, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case LEFT_U_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 5, position.y - 4, { -1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x - 3, position.y - 15, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_M_BOT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 25, position.y + 17, { +2, +1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 20, position.y + 13, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_B_BOT:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 17, position.y + 22, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 12, position.y + 19, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_M_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 21, position.y + 5, { +2, -1 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 16, position.y + 1, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;
			case RIGHT_U_UP:
				App->particles->AddParticle(App->particles->Enemy_Laser, position.x + 17, position.y - 1, { +1, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->Enemy_Exp, position.x + 14, position.y - 12, { 0, 0 }, nullrect, COLLIDER_NONE);
				break;

			}
			last_shoot = SDL_GetTicks();
		}
	}
}


void Soldier1::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);

}