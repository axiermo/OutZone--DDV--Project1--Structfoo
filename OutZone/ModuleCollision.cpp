#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = true;
	matrix[COLLIDER_WALL][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_WALL][COLLIDER_TURRET] = false;
	matrix[COLLIDER_WALL][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_DOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DOOR][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_DOOR][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DOOR][COLLIDER_GOD] = true;
	matrix[COLLIDER_DOOR][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_DOOR][COLLIDER_TURRET] = false;
	matrix[COLLIDER_DOOR][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_ENERGY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENERGY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_GOD] = true;
	matrix[COLLIDER_ENERGY][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_TURRET] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_UPGRADE][COLLIDER_WALL] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_UPGRADE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_GOD] = true;
	matrix[COLLIDER_UPGRADE][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_TURRET] = false;
	matrix[COLLIDER_UPGRADE][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_GOD] = true;
	matrix[COLLIDER_BOMB][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_TURRET] = false;
	matrix[COLLIDER_BOMB][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_CHANGE][COLLIDER_WALL] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CHANGE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_GOD] = true;
	matrix[COLLIDER_CHANGE][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_TURRET] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_BOX][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOX][COLLIDER_GOD] = true;
	matrix[COLLIDER_BOX][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_BOX][COLLIDER_TURRET] = false;
	matrix[COLLIDER_BOX][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TURRET] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_TRUCK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_MAZURKA] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_TURRET] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_EXPLOSION] = true;

	matrix[COLLIDER_RED_SOLDIER][COLLIDER_WALL] = true;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_GOD] = true;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_TURRET] = true;
	matrix[COLLIDER_RED_SOLDIER][COLLIDER_EXPLOSION] = true;

	matrix[COLLIDER_TURRET][COLLIDER_WALL] = true;
	matrix[COLLIDER_TURRET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TURRET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_TURRET][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_TURRET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TURRET][COLLIDER_GOD] = true;
	matrix[COLLIDER_TURRET][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_TURRET][COLLIDER_TURRET] = false;
	matrix[COLLIDER_TURRET][COLLIDER_EXPLOSION] = true;
	matrix[COLLIDER_TURRET][COLLIDER_PLAYER_SHOT] = true;

	matrix[COLLIDER_BIG_TURRET][COLLIDER_WALL] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_GOD] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_TURRET] = false;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_EXPLOSION] = true;
	matrix[COLLIDER_BIG_TURRET][COLLIDER_PLAYER_SHOT] = true;

	matrix[COLLIDER_DEAD][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEAD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_DEAD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DEAD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_DEAD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DEAD][COLLIDER_GOD] = false;
	matrix[COLLIDER_DEAD][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_DEAD][COLLIDER_TURRET] = false;
	matrix[COLLIDER_DEAD][COLLIDER_BORDER] = true;
	matrix[COLLIDER_DEAD][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DEAD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_UPGRADE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BORDER_TOP] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_MAZURKA] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TRUCK] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TURRET] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BIG_TURRET] = true;

	matrix[COLLIDER_TRUCK][COLLIDER_PLAYER_SHOT] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TURRET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BIG_TURRET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DEAD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_EXPLOSION] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_UPGRADE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_MAZURKA] = false;

	matrix[COLLIDER_GOD][COLLIDER_WALL] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_GOD][COLLIDER_TURRET] = true;
	matrix[COLLIDER_GOD][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_TURRET_WALL][COLLIDER_TURRET_WALL] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_GOD] = true;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_TURRET] = false;
	matrix[COLLIDER_TURRET_WALL][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_BORDER][COLLIDER_WALL] = true;
	matrix[COLLIDER_BORDER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BORDER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BORDER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BORDER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BORDER][COLLIDER_GOD] = false;
	matrix[COLLIDER_BORDER][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_BORDER][COLLIDER_TURRET] = true;
	matrix[COLLIDER_BORDER][COLLIDER_DEAD] = true;
	matrix[COLLIDER_BORDER][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_BORDER_TOP][COLLIDER_WALL] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_GOD] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_TURRET] = false;
	matrix[COLLIDER_BORDER_TOP][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_EXPLOSION][COLLIDER_TURRET] = true;
	matrix[COLLIDER_EXPLOSION][COLLIDER_WALL] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_EXPLOSION][COLLIDER_GOD] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_EXPLOSION] = false;

	matrix[COLLIDER_MAZURKA][COLLIDER_WALL] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_MAZURKA][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_GOD] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_TURRET_WALL] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_TURRET] = false;
	matrix[COLLIDER_MAZURKA][COLLIDER_EXPLOSION] = true;
}

ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

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
		case COLLIDER_BIG_TURRET: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_DEAD: 
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_BORDER: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_BORDER_TOP: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_GOD:
			App->render->DrawQuad(colliders[i]->rect, 50, 200, 255, alpha);
			break;
		case COLLIDER_TURRET_WALL:
			App->render->DrawQuad(colliders[i]->rect, 125, 0, 255, alpha);
			break;
		case COLLIDER_EXPLOSION:
			App->render->DrawQuad(colliders[i]->rect, 40, 75, 200, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_RED_SOLDIER: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_TRUCK: 
			App->render->DrawQuad(colliders[i]->rect, 255,40, 20, alpha);
			break;
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
	if (collider != nullptr)
	{
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
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

