#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 500

#include "Module.h"
#include "Globals.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY, // ALL
	COLLIDER_TURRET,  // GREY TURRET
	COLLIDER_BIG_TURRET,
	COLLIDER_TRUCK,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_EXPLOSION,
	COLLIDER_GOD,
	COLLIDER_TURRET_WALL,
	COLLIDER_BORDER,
	COLLIDER_BORDER_TOP,
	COLLIDER_DEAD,
	COLLIDER_CHANGE,
	COLLIDER_UPGRADE,
	COLLIDER_ENERGY,
	COLLIDER_RED_SOLDIER,
	COLLIDER_BOMB,
	COLLIDER_BOX,
	COLLIDER_DOOR,
	COLLIDER_MAZURKA,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	Directions ColliderHit(const SDL_Rect& r) const;
	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__