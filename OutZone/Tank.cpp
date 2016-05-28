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
		//coming from right
	case 1:
		path.PushBack({ -1.5f, 0.0f },75, &tankanim);

		path.PushBack({ -1.1f, 0.4f }, 35, &tankanim);
		path.PushBack({ -0.9f, 0.6f }, 35, &tankanim);
		path.PushBack({ -0.4f, 1.1f }, 35, &tankanim);
		path.PushBack({ 0.0f, 1.2f }, 35, &tankanim);
		path.PushBack({ 0.4f, 1.1f }, 35, &tankanim);
		path.PushBack({ 0.9f, 0.6f }, 35, &tankanim);
		path.PushBack({ 1.1f, 0.4f }, 35, &tankanim);

		path.PushBack({ 1.5f, 0.0f }, 200, &tankanim);
		break;
		
		//coming from left 2 cicles
	case 2:
		path.PushBack({ -0.9f, 0.0f }, 50, &tankanim);
		path.PushBack({ 0.5f, 0.8f }, 150, &tankanim);
		path.PushBack({ 0.7f, 0.3f }, 150, &tankanim);
		path.PushBack({ 0.9f, 0.1f }, 150, &tankanim);
		path.PushBack({ 0.5f, 0.8f }, 150, &tankanim);
		path.PushBack({ 0.7f, 0.3f }, 150, &tankanim);
		path.PushBack({ 0.9f, 0.1f }, 150, &tankanim); 
		path.PushBack({ -0.9f, 0.0f }, 50, &tankanim);
		path.PushBack({ 0.5f, 0.8f }, 150, &tankanim);
		path.PushBack({ 0.7f, 0.3f }, 150, &tankanim);
		path.PushBack({ 0.9f, 0.1f }, 150, &tankanim);
		path.PushBack({ 0.5f, 0.8f }, 150, &tankanim);
		path.PushBack({ 0.7f, 0.3f }, 150, &tankanim);
		path.PushBack({ 0.9f, 0.1f }, 150, &tankanim);
		break;
	}

	//Set the automathic paths here

	original_pos.x = x;
	original_pos.y = y;

}

void Tank::Move()
{



	// Move with the path
	position = original_pos + path.GetCurrentSpeed();


}

void Tank::Shoot()
{
	float distance = position.DistanceTo(App->player->position);
	next_shoot = SDL_GetTicks();
	if (next_shoot - last_shoot > 1800 && distance>100 && distance <136)
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


void Tank::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(curr_animation->GetCurrentFrame()), -1.0f);

}