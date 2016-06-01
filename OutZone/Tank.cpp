#include "Application.h"
#include "Tank.h"
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

Tank::Tank(int x, int y, int subtype) :Enemy(x, y, subtype)
{
	tankanim.PushBack({ 10, 1308, 46, 47 });
	tankanim.PushBack({ 64, 1308, 44, 41 });
	tankanim.PushBack({ 112, 1308, 46, 47 });
	tankanim.PushBack({ 10, 1360, 46, 47 });
	tankanim.PushBack({ 64, 1360, 45, 46 });
	tankanim.PushBack({ 112, 1360, 46, 47 });
	tankanim.speed = 0.2f;

	curr_animation = &tankanim;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	switch (subtype)
	{
	case 1:
		path.PushBack({ -2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 300, &tankanim);
		break;
	case 2:
		path.PushBack({ 0.0f, 0.0f }, 20, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 300, &tankanim);
		break;
	case 3:
		path.PushBack({ 0.0f, 0.0f }, 40, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 300, &tankanim);
		break;
	case 4:
		path.PushBack({ 0.0f, 0.0f }, 60, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 300, &tankanim);
		//coming from left 2 cicles
	case 5:
		path.PushBack({ 2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ -2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, -2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 10, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 300, &tankanim);
		break;
	case 6:
		path.PushBack({ 0.0f, 0.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ -2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, -2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 10, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 300, &tankanim);
		break;
	case 7:
		path.PushBack({ 0.0f, 0.0f }, 40, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ -2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, -2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 10, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 300, &tankanim);
		break;
	case 8:
		path.PushBack({ 0.0f, 0.0f }, 60, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 30, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 15, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ -2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, -2.8f }, 20, &tankanim);
		path.PushBack({ 2.5f, -2.0f }, 20, &tankanim);
		path.PushBack({ 2.8f, 0.0f }, 20, &tankanim);
		path.PushBack({ 2.5f, 2.0f }, 20, &tankanim);
		path.PushBack({ 0.0f, 2.8f }, 20, &tankanim);
		path.PushBack({ -2.5f, 2.0f }, 10, &tankanim);
		path.PushBack({ -2.8f, 0.0f }, 300, &tankanim);
		break;
	}
	if (x < 100)
		left = true;
	else
		left = false;


	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

	lives = 8;
}

void Tank::Move()
{

	if (App->render->camera.y > 4740 && left)
		position = original_pos + path.GetCurrentSpeed();
	else if (App->render->camera.y > 4880)
		position = original_pos + path.GetCurrentSpeed();
	else
		path.Reset();


}

void Tank::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 1000)
	{
		App->particles->AddParticle(App->particles->TankMissile, position.x + 10, position.y + 22, { 0, +5 }, { 0, 0, 16, 30 }, COLLIDER_ENEMY_SHOT);
		last_shoot = SDL_GetTicks();
	}
}




void Tank::Draw()
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