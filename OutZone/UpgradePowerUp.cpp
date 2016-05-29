#include "Application.h"
#include "UpgradePowerUp.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

UpgradePowerUp::UpgradePowerUp(int x, int y) : Enemy(x, y, 0)
{
	rotate.PushBack({ 407, 515, 16, 16 }); 
	rotate.PushBack({ 407, 533, 16, 16 });
	rotate.speed = 0.2f;

	lives = 1;

	animation = &rotate;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_UPGRADE, App->enemies);

	position.x = x;
	position.y = y;
}

void UpgradePowerUp::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(rotate.GetCurrentFrame()), -1.0f);
}