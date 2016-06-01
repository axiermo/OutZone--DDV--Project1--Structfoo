#include "Application.h"
#include "BlueSoldier.h"
#include "ModuleCollision.h"
#include "Path.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"

#define PI 3.1415926

BlueSoldier::BlueSoldier(int x, int y, int subtype) :Enemy(x, y, subtype)
{
	up.PushBack({ 166, 1059, 26, 36 });
	up.PushBack({ 203, 1058, 27, 37 });
	up.PushBack({ 241, 1059, 26, 35 });
	up.PushBack({ 274, 1059, 26, 35 });
	up.speed = 0.1f;

	right.PushBack({ 167, 1148, 28, 32 });
	right.PushBack({ 204, 1149, 25, 32 });
	right.PushBack({ 240, 1148, 27, 32 });
	right.PushBack({ 280, 1148, 25, 33 });
	right.speed = 0.1f;

	left.PushBack({ 174, 1329, 25, 32 });
	left.PushBack({ 209, 1329, 28, 32 });
	left.PushBack({ 246, 1328, 25, 33 });
	left.PushBack({ 283, 1328, 25, 33 });
	left.speed = 0.1f;

	down.PushBack({ 167, 1235, 27, 35 });
	down.PushBack({ 203, 1238, 27, 32 });
	down.PushBack({ 240, 1237, 28, 33 });
	down.PushBack({ 279, 1239, 27, 31 });
	down.speed = 0.1f;

	upleft.PushBack({ 177, 1369, 26, 35 });
	upleft.PushBack({ 211, 1369, 28, 35 });
	upleft.PushBack({ 247, 1370, 28, 34 });
	upleft.PushBack({ 284, 1371, 28, 33 });
	upleft.speed = 0.1f;

	downleft.PushBack({ 173, 1282, 27, 33 });
	downleft.PushBack({ 211, 1282, 27, 34 });
	downleft.PushBack({ 248, 1282, 25, 34 });
	downleft.PushBack({ 280, 1282, 27, 34 });
	downleft.speed = 0.1f;

	downright.PushBack({ 166, 1192, 27, 34 });
	downright.PushBack({ 201, 1193, 26, 33 });
	downright.PushBack({ 238, 1193, 27, 33 });
	downright.PushBack({ 276, 1193, 26, 35 });
	downright.speed = 0.1f;

	upright.PushBack({ 166, 1103, 29, 34 });
	upright.PushBack({ 204, 1103, 26, 34 });
	upright.PushBack({ 243, 1103, 24, 33 });
	upright.PushBack({ 280, 1103, 25, 36 });
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
		path.PushBack({ 0.0f, 1.0f }, 160, &down);
		path.PushBack({ -0.2f, -1.3f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 4:
		path.PushBack({ 0.0f, 1.0f }, 164, &down);
		path.PushBack({ 0.2f, -0.6f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 5:
		path.PushBack({ 0.0f, 1.0f }, 168, &down);
		path.PushBack({ -0.2f, -1.4f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 6:
		path.PushBack({ 0.0f, 1.0f }, 172, &down);
		path.PushBack({ 0.2f, -0.6f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	//3,4,5,6 first top truck soldiers
	case 7:
		path.PushBack({ 0.0f, 1.0f }, 180, &down);
		path.PushBack({ 0.3f, -1.2f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 8:
		path.PushBack({ 0.0f, 1.0f }, 184, &down);
		path.PushBack({ -0.1f, -0.35f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 9:
		path.PushBack({ 0.0f, 1.0f }, 188, &down);
		path.PushBack({ 0.2f, -1.1f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 10:
		path.PushBack({ 0.0f, 1.0f }, 192, &down);
		path.PushBack({ -0.1f, -0.5f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
		//7,8,9,10 second top truck soldiers
	case 11:
		path.PushBack({ 0.0f, 1.0f }, 180, &down);
		path.PushBack({ -0.3f, -1.5f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 12:
		path.PushBack({ 0.0f, 1.0f }, 184, &down);
		path.PushBack({ 0.1f, -0.35f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 13:
		path.PushBack({ 0.0f, 1.0f }, 188, &down);
		path.PushBack({ 0.0f, -1.5f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 14:
		path.PushBack({ 0.0f, 1.0f }, 192, &down);
		path.PushBack({ 0.1f, -0.35f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
		//11,12,13,14 second top truck soldiers
	case 15:
		path.PushBack({ 0.0f, 1.0f }, 240, &down);
		path.PushBack({ -0.3f, -0.8f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 16:
		path.PushBack({ 0.0f, 1.0f }, 244, &down);
		path.PushBack({ 0.4f, -1.4f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 17:
		path.PushBack({ 0.0f, 1.0f }, 248, &down);
		path.PushBack({ -0.5f, -0.9f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	case 18:
		path.PushBack({ 0.0f, 1.0f }, 252, &down);
		path.PushBack({ 0.9f, -0.8f }, 40, &down);
		path.PushBack({ 0.0f, 1.0f }, 500, &down);
		break;
	}
	//Set the automathic paths here
	original_pos.x = x;
	original_pos.y = y;

}

void BlueSoldier::SelectAnimation(Directions direction)
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
void BlueSoldier::Move()
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
	position = original_pos + path.GetCurrentSpeed();


}

void BlueSoldier::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();

	if (App->player->position.y - position.y < 85 || appeared)
	{
		appeared = true;
		if (next_shoot - last_shoot > 1800 && distance > 100 && distance < 136)
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


void BlueSoldier::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (hit == false) App->render->Blit(App->enemies->sprites, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);
	else
	{
		App->render->Blit(App->enemies->sprites2, position.x, position.y, &curr_animation->GetActualFrame(), -1.0f);
		t++;

		if (t == 3)
		{
			hit = false;
			t = 0;
		}
	}
}