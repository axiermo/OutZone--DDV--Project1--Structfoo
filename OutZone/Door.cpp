#include "Application.h"
#include "Door.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

Door::Door(int x, int y) : Enemy (x, y, 0)
{
	anim.PushBack({ 19, 665, 114, 106 }); // top

	animation = &anim;

	collider = App->collision->AddCollider({ 0, 0, 111, 84}, COLLIDER_ENEMY, App->enemies);

	lives = 14;

	position.x = x;
	position.y = y;

	direction = UP;
}

void Door::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &anim.GetActualFrame(),-1.0f);
}