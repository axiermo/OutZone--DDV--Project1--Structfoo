#include "Application.h"
#include "RedSoldier.h"
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

RedSoldier::RedSoldier(int x, int y, int subtype) :Enemy(x, y, subtype)
{

	walk.PushBack({ 12, 492, 28, 35 }); // UP
	walk.PushBack({ 17, 533, 24, 35 }); // RIGHT
	walk.PushBack({ 12, 613, 23, 33 }); // LEFT
	walk.PushBack({ 10, 573, 28, 35 }); // DOWN

	walk.PushBack({ 80, 493, 25, 35 }); // UP_RIGHT
	walk.PushBack({ 77, 612, 27, 35 }); // UP_LEFT
	walk.PushBack({ 75, 533, 27, 35 }); // DOWN_RIGHT
	walk.PushBack({ 76, 573, 27, 36 }); //DOWN_LEFT

	walk.PushBack({ 44, 613, 24, 35 }); // LEFT_M_UP
	walk.PushBack({ 110, 612, 26, 35 }); // LEFT_U_UP
	walk.PushBack({ 114, 492, 22, 36 }); // RIGHT_M_UP 
	walk.PushBack({ 46, 493, 28, 36 }); // RIGHT_U_UP

	walk.PushBack({ 107, 534, 29, 34 }); // RIGHT_B_BOT
	walk.PushBack({ 46, 533, 26, 35 }); // RIGHT_M_BOT
	walk.PushBack({ 108, 573, 26, 35 }); // LEFT_M_BOT
	walk.PushBack({ 45, 574, 27, 35 }); // LEFT_B_BOT

	walk.speed = 0.5f;

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	switch (subtype)
	{
	case 1:
		path.PushBack({ 0.0f, 0.9f }, 120, &walk);
		path.PushBack({ 0.5f, 0.8f }, 150, &walk);
		path.PushBack({ 0.7f, 0.3f }, 150, &walk);
		path.PushBack({ 0.9f, 0.1f }, 80, &walk);
		path.PushBack({ 0.9f, 0.0f }, 200, &walk);
		break;
	case 2:
		path.PushBack({ 0.0f, 1.0f }, 150, &walk);
		break;
	case 3:
		path.PushBack({ 0.0f, 0.0f }, 150, &walk);
		break;
	case 4:
		path.PushBack({ -0.3f, 0.7f }, 50, &walk);
		path.PushBack({ 0.0f, 0.0f }, 60, &walk);
		path.PushBack({ -0.5f, 0.8f }, 80, &walk);
		path.PushBack({ -0.7f, 0.8f }, 150, &walk);
		break;
	case 5://!!!
		path.PushBack({ 0.0f, -1.0f }, 40, &walk);
		path.PushBack({ 0.7f, 0.0f }, 150, &walk);	//x pixels
		// we willneed more cases for this one
		break;
	case 6:
		path.PushBack({ -0.8f, 0.0f }, 150, &walk);
		path.PushBack({ -0.8f, 0.4f }, 40, &walk);
		path.PushBack({ -0.8f, -0.4f }, 80, &walk);
		path.PushBack({ -0.8f, 0.4f }, 40, &walk);
		path.PushBack({ -0.8f, 0.0f }, 150, &walk);
		break;
	case 7:
		path.PushBack({ -0.8f, 0.0f }, 150, &walk);
		path.PushBack({ -0.8f, 0.0f }, 40, &walk);
		path.PushBack({ 0.0f, 0.4f }, 80, &walk);
	case 8:
		path.PushBack({ -0.8f, 0.0f }, 150, &walk);
		path.PushBack({ 0.8f, 0.0f }, 40, &walk);
		path.PushBack({ -0.8f, -0.4f }, 80, &walk);




	}

	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

}

void RedSoldier::Move()
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

void RedSoldier::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();

	if (!destroyed && (App->player->position.y - position.y < 150 || appeared))
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


void RedSoldier::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &walk.GetActualFrame(), -1.0f);

}