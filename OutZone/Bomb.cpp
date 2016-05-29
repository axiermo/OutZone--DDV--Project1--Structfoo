#include "Application.h"
#include "Bomb.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"

Bomb::Bomb(int x, int y) : Enemy(x, y, 0)
{
	anim.PushBack({ 461, 552, 20, 20 });
	anim.PushBack({ 433, 552, 20, 20 });
	anim.speed = 0.2f;

	lives = 1;

	animation = &anim;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_BOMB, App->enemies);

	position.x = x;
	position.y = y;
}

void Bomb::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(anim.GetCurrentFrame()), -1.0f);
}