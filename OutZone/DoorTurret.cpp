#include "Application.h"
#include "DoorTurret.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

#define PI 3.1415926

DoorTurret::DoorTurret(int x, int y) : Enemy(x, y)
{
	anim.PushBack({ 90, 793, 26, 40 }); // UP
	anim.PushBack({ 119, 793, 26, 40 }); // UP
	anim.speed = 1.0f;
	animation = &anim;

	lives = 8;

	collider = App->collision->AddCollider({ 0, 0, 26, 40 }, COLLIDER_TURRET, App->enemies);

	position.x = x;
	position.y = y;

	last_shoot = SDL_GetTicks();
	//TODO change the sprite to the hole in the ground

	direction = DOWN_LEFT;
	previous = LEFT_B_DOWN;

}




void DoorTurret::Move()
{

	if (direction == DOWN_LEFT && previous == LEFT_B_DOWN)
	{
		direction = LEFT_B_DOWN;
		previous = DOWN_LEFT;
	}
	else if (direction == LEFT_B_DOWN && previous == DOWN_LEFT)
	{
		direction = DOWN;
		previous = LEFT_B_DOWN;

	}
	else if (direction == DOWN && previous == LEFT_B_DOWN)
	{
		direction = RIGHT_B_BOT;
		previous = DOWN;

	}
	else if (direction == RIGHT_B_BOT && previous == DOWN)
	{
		direction = DOWN_RIGHT;
		previous = RIGHT_B_BOT;

	}
	else if (direction == DOWN_RIGHT && previous == RIGHT_B_BOT)
	{
		direction = RIGHT_B_BOT;
		previous = DOWN_RIGHT;

	}
	else if (direction == RIGHT_B_BOT && previous == DOWN_RIGHT)
	{
		direction = DOWN;
		previous = RIGHT_B_BOT;

	}
	else if (direction == DOWN && previous == RIGHT_B_BOT)
	{
		direction = LEFT_B_DOWN;
		previous = DOWN;

	}
	else if (direction == LEFT_B_DOWN && previous == DOWN)
	{
		direction = DOWN_LEFT;
		previous = LEFT_B_DOWN;

	}






}

void DoorTurret::Shoot()
{
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 1800)
	{
		switch (direction)
		{
		case DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 11, position.y + 12, { 0, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_LEFT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x - 11, position.y + 12, { -2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case DOWN_RIGHT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +2, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case RIGHT_B_BOT:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { +1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		case LEFT_B_DOWN:
			App->particles->AddParticle(App->particles->basic_bullet, position.x + 12, position.y + 12, { -1, +2 }, { 0, 0, 6, 6 }, COLLIDER_ENEMY_SHOT);
			break;
		}
		last_shoot = SDL_GetTicks();
	}
}


void DoorTurret::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(),-1.0f);
}