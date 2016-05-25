#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

Enemy::Enemy(int x, int y, int subtype) : position(x, y), subtype(subtype), collider(nullptr)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(App->enemies->sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}