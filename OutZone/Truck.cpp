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
	down.PushBack({ 492, 164, 80, 124 });
	down.PushBack({ 492, 292, 80, 123 });
	down.PushBack({ 492, 420, 80, 124 });
	down.PushBack({ 492, 567, 80, 125 });

	stop.PushBack({ 492, 164, 80, 124 });

	wheels.PushBack({ 315, 584, 66, 24 });
	
	dead.PushBack({ 520, 17, 96, 120});//hole

	down.speed = 0.1f;
	lives = 40;
	curr_animation = &down;

	collider = App->collision->AddCollider({ 0, 0, 75, 120 }, COLLIDER_TYPE::COLLIDER_TRUCK, (Module*)App->enemies);
	
	switch (subtype)
	{
	case 1:
		path.PushBack({ 0.0f, 1.0f }, 200, &down);
		break;
	case 2:
		path.PushBack({ 0.0f, 1.3f }, 130, &down);
		path.PushBack({ 0.0f, 0.0f }, 200, &stop);
		path.PushBack({ 0.0f, 0.9f }, 500, &down);
		break;


	}
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
	case IDLE:
		curr_animation = &stop;
		position.y += 0;
		break;
	case UP://dead
		curr_animation = &dead;
		position.y += 0;
		break;

	}
}
//TODO
void Truck::Move()
{
	if (!path.Moving() && !destroyed)
		SelectAnimation(IDLE);
	
	else if (!destroyed)
		SelectAnimation(DOWN);
	else
		SelectAnimation(UP);
	


	// Move with the path
	if (!destroyed)
	position = original_pos + path.GetCurrentSpeed();


}




void Truck::Draw()
{
	if (collider != nullptr && !destroyed)
		collider->SetPos(position.x, position.y);
	else
	{
		collider->rect.h = 1;
		collider->type = COLLIDER_DEAD;

	}
		

	// Green blit ----------------------------
	if (!destroyed){
		if (hit == false)
			App->render->Blit(App->enemies->sprites, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);
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
	else
		App->render->Blit(App->enemies->sprites, position.x - 15, position.y, &(dead.GetCurrentFrame()), -1.0f);
		
}