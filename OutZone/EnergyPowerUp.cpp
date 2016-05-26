#include "Application.h"
#include "EnergyPowerUp.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"



EnergyPowerUp::EnergyPowerUp(int x, int y) : Enemy(x, y, 0)
{
	rotate.PushBack({ 343, 552, 16, 16 }); // UP
	rotate.PushBack({ 363, 552, 16, 16 });
	rotate.speed = 0.2f;

	lives = 1;

	animation = &rotate;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_NONE, App->enemies);

	position.x = x;
	position.y = y;


}

void EnergyPowerUp::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &rotate.GetCurrentFrame(), -1.0f);
}