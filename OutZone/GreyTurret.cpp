#include "Application.h"
#include "GreyTurret.h"
#include "ModuleCollision.h"
#include"ModulePlayer.h"
#include"ModuleRender.h"
#include"ModuleParticles.h"

#define PI 3.1415926

GreyTurret::GreyTurret(int x, int y) : Enemy(x, y)
{
	//enum Directions { IDLE, UP, RIGHT, LEFT, DOWN, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT };
	rotate.PushBack({ 11, 6, 27, 31 }); // top
	rotate.PushBack({ 11, 45, 28, 27 }); // right
	rotate.PushBack({ 9, 117, 30, 27 }); // left
	rotate.PushBack({ 9, 80, 29, 29 }); // bot
	rotate.PushBack({ 74, 8, 27, 29 }); // top right
	rotate.PushBack({ 76, 114, 23, 29 }); // top left
	rotate.PushBack({ 74, 44, 28, 28 }); // bot right
	rotate.PushBack({ 76, 80, 26, 28 }); // bot left

	animation = &rotate;

	sprite = App->particles->greyturret;
	collider = App->collision->AddCollider({ 0, 0, 24, 30 }, COLLIDER_TYPE::COLLIDER_TURRET, (Module*)App->enemies);

	position.x = x;
	position.y = y;

	last_shoot = SDL_GetTicks();
	

	//bullet = &App->particles->green_basic_bullet;
	//shoot_start = &App->particles->green_basic_bullet_start;
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

	if (angle>225&& angle<315)
	{
		// its down
		rotate.setframe(UP);
		direction = UP;
	}
	else if (angle>67.5 && angle<112.5)
	{
		rotate.setframe(DOWN);
		direction = DOWN;
	}
	else if (angle==180)
	{
		rotate.setframe(LEFT);
		direction = LEFT;
	}
	else if (angle<45 && angle>0)
	{
		rotate.setframe(RIGHT);
		direction = RIGHT;
	}
	else if (angle>22.5 && angle<67.5)
	{
		rotate.setframe(DOWN_RIGHT);
		direction = DOWN_RIGHT;
	}
	
	else if (player_position_x < position.x && player_position_y < position.y)
	{
		rotate.setframe(UP_LEFT);
		direction = UP_LEFT;
	}
	
	else if (player_position_x > position.x && player_position_y < position.y)
	{
		rotate.setframe(UP_RIGHT);
		direction = UP_RIGHT;
	}
	else if (angle<180 && angle>135)
	{
		rotate.setframe(DOWN_LEFT);
		direction = DOWN_LEFT;
	}
}

void GreyTurret::Shoot()
{
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 350)
	{
		switch (direction){
		case UP:
			
			App->particles->AddParticle(App->particles->laserup, position.x + 18, position.y - 10, { 0, -5 }, { 0, 0, 6, 18 }, COLLIDER_ENEMY_SHOT);

			break;
		case DOWN:
			
			App->particles->AddParticle(App->particles->laserup, position.x + 5, position.y + 19, { 0, +5 }, { 0, 0, 6, 18 }, COLLIDER_ENEMY_SHOT);

			break;
		case LEFT:
			
			App->particles->AddParticle(App->particles->laserright, position.x - 8, position.y + 5, { -5, 0 }, { 0, 0, 18, 6 }, COLLIDER_ENEMY_SHOT);

			break;
		case RIGHT:
			
			App->particles->AddParticle(App->particles->laserright, position.x + 29, position.y + 10, { +5, 0 }, { 0, 0, 18, 6 }, COLLIDER_ENEMY_SHOT);

			break;
		case UP_LEFT:
			
			App->particles->AddParticle(App->particles->laserupleft, position.x + 5, position.y - 10, { -5, -5 }, { 0, 0, 14, 14 }, COLLIDER_ENEMY_SHOT);

			break;
		case UP_RIGHT:
			
			App->particles->AddParticle(App->particles->laserupright, position.x + 20, position.y - 10, { +5, -5 }, { 0, 0, 14, 14 }, COLLIDER_ENEMY_SHOT);

			break;
		case DOWN_LEFT:
			
			App->particles->AddParticle(App->particles->laserupright, position.x - 11, position.y + 12, { -5, +5 }, { 0, 0, 14, 14 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_RIGHT:
			
			App->particles->AddParticle(App->particles->laserupleft, position.x + 12, position.y + 12, { +5, +5 }, { 0, 0, 14, 14 }, COLLIDER_ENEMY_SHOT);

			break;

		}
		last_shoot = SDL_GetTicks();

	}

}


void GreyTurret::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(sprite, position.x, position.y, &rotate.GetActualFrame());
}