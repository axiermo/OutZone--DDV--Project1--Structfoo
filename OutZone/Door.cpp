#include "Application.h"
#include "Door.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

Door::Door(int x, int y) : Enemy(x, y)
{
	rotate.PushBack({ 19, 665, 111, 65 }); // top

	animation = &rotate;

	collider = App->collision->AddCollider({ 0, 0, 111, 65 }, COLLIDER_DOOR, App->enemies);

	position.x = x;
	position.y = y;

	//last_shoot = SDL_GetTicks();

	direction = UP;
}


/*void Door::Move()
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
		//rotate.setframe(RIGHT_M_BOT);
		//direction = RIGHT_M_BOT;

	}
	else if (dx > 0 && dy > 0 && angle>33.75 && angle < 56.25)
	{
		rotate.setframe(DOWN_RIGHT);
		direction = DOWN_RIGHT;

	}
	else if (dx > 0 && dy > 0 && angle>56.25 && angle < 78.25)
	{
		//rotate.setframe(RIGHT_B_BOT);
		//direction = RIGHT_B_BOT;
	}
	else if (dx > 0 && dy > 0 && angle>78.25 && angle < 90)
	{
		rotate.setframe(DOWN);
		direction = DOWN;
	}
	//bot left quadrant
	else if (dx < 0 && dy>0 && angle<-0.1 && angle>-11.25)
	{
		rotate.setframe(LEFT);
		direction = LEFT;

	}
	else if (dx < 0 && dy>0 && angle<-11.25&& angle>-33.75)
	{
		//rotate.setframe(LEFT_M_DOWN);
		//direction = LEFT_M_DOWN;

	}
	else if (dx < 0 && dy>0 && angle<-33.75 && angle>-56.25)
	{
		rotate.setframe(DOWN_LEFT);
		direction = DOWN_LEFT;

	}
	else if (dx < 0 && dy>0 && angle < -56.25 && angle - 78.25)
	{
		//rotate.setframe(LEFT_B_DOWN);
		//direction = LEFT_B_DOWN;
	}
	else if (dx < 0 && dy>0 && angle<-78.25 && angle > -89.9)
	{
		rotate.setframe(DOWN);
		direction = DOWN;
	}

	//top left quadrant
	else if (dx < 0 && dy < 0 && angle>0 && angle<11.25)
	{
		rotate.setframe(LEFT);
		direction = LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>11.25 && angle < 33.75)
	{
		//rotate.setframe(LEFT_M_UP);
		//direction = LEFT_M_UP;
	}
	else if (dx < 0 && dy < 0 && angle>33.75 && angle < 56.25)
	{
		rotate.setframe(UP_LEFT);
		direction = UP_LEFT;
	}
	else if (dx < 0 && dy < 0 && angle>56.25 && angle < 78.25)
	{
		//rotate.setframe(LEFT_U_UP);
		//direction = LEFT_U_UP;
	}
	else if (dx < 0 && dy < 0 && angle>78.25 && angle < 90)
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
	else if (dx>0 && dy<0 && angle > -11.25 && angle > -33.75)
	{
		//rotate.setframe(RIGHT_M_UP);
		//direction = RIGHT_M_UP;
	}
	else if (dx>0 && dy<0 && angle > -33.75 && angle > -56.25)
	{
		rotate.setframe(UP_RIGHT);
		direction = UP_RIGHT;
	}
	else if (dx>0 && dy<0 && angle > -56.25 && angle > -78.25)
	{
		//rotate.setframe(RIGHT_U_UP);
		//direction = RIGHT_U_UP;
	}
	else if (dx>0 && dy<0 && angle < -78.25 && angle > -89.1)
	{
		rotate.setframe(UP);
		direction = UP;
	}
}

void Door::Shoot()
{
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 1800)
	{
		switch (direction)
		{
		case UP:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 18, position.y - 10, { 0, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 5, position.y + 19, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 8, position.y + 5, { -2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 29, position.y + 10, { +2, 0 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case UP_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 5, position.y - 10, { -2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case UP_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 20, position.y - 10, { +2, -2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 11, position.y + 12, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		}
		last_shoot = SDL_GetTicks();
	}
}*/


void Door::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &rotate.GetActualFrame());
}