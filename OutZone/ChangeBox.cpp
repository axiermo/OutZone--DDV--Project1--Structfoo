#include "Application.h"
#include "ChangeBox.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"



ChangeBox::ChangeBox(int x, int y) : Enemy(x, y, 0)
{
	rotate.PushBack({ 363, 510, 32, 32 }); // UP


	lives = 2;

	animation = &rotate;

	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_ENEMY, App->enemies);

	position.x = x;
	position.y = y;


}

void ChangeBox::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &rotate.GetActualFrame(), -1.0f);
}