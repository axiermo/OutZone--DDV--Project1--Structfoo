#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_TURRET] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = true;
	matrix[COLLIDER_WALL][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_WALL][COLLIDER_DOOR] = false;


	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_TURRET] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DOOR] = true;


	matrix[COLLIDER_TURRET][COLLIDER_WALL] = true;
	matrix[COLLIDER_TURRET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TURRET][COLLIDER_TURRET] = false;
	matrix[COLLIDER_TURRET][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_TURRET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TURRET][COLLIDER_GOD] = true;
	matrix[COLLIDER_TURRET][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_TURRET][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TURRET] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DOOR] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TURRET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DOOR] = true;


	matrix[COLLIDER_GOD][COLLIDER_WALL] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GOD][COLLIDER_TURRET] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_TURRET_WALL] = true;

	matrix[COLLIDER_TURRET_WALL][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_TURRET] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_GOD] = true;

	matrix[COLLIDER_DOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DOOR][COLLIDER_TURRET] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_DOOR][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_DOOR][COLLIDER_DOOR] = false;
}

ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				COLLIDER_TYPE c1_type = c1->type;
				if (matrix[c1->type][c2->type] && c1->callback){
					c1->callback->OnCollision(c1, c2);
					if (c2->type == COLLIDER_PLAYER_SHOT)
						c2->callback->OnCollision(c2, c1);
				}
				if (c1->type != c1_type) continue;

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255,alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_TURRET: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_GOD:
			App->render->DrawQuad(colliders[i]->rect, 50, 200, 255, alpha);
			break;
		case COLLIDER_TURRET_WALL:
			App->render->DrawQuad(colliders[i]->rect, 125, 0, 255, alpha);
			break;
		case COLLIDER_DOOR:
			App->render->DrawQuad(colliders[i]->rect, 128, 128, 128, alpha);
		}
	}
}

bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}
