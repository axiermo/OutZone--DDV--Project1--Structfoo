#include "Application.h"
#include "Truck.h"
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


Truck::Truck(int x, int y, int subtype) : Enemy(x, y, subtype)
{
	//TODO
	down.PushBack({});
	down.PushBack({});
	down.PushBack({});
	down.PushBack({});
	down.speed = 0.1f;

	stop.PushBack({});
	stop.PushBack({});
	stop.PushBack({});
	stop.PushBack({});
	stop.speed = 0.1f;

	curr_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	switch (subtype)
	{
	case 1:
		path.PushBack({ 0.0f, 0.9f }, 50, &down);
		break;


	}

	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

}

void Truck::SelectAnimation(Directions direction)
{
	int speed = 2;
	last_animation = curr_animation;

	switch (direction)
	{
	case DOWN:
		curr_animation = &down;
		position.y += speed;
		break;
	//case DOWN_RIGHT:
		//curr_animation = &downright;
		//break;
	}
}
//TODO
void Truck::Move()
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




void Truck::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);

}