#include "Application.h"
#include "GreyTurret.h"
#include "ModuleCollision.h"

GreyTurret::GreyTurret(int x, int y) : Enemy(x, y)
{

	bot.PushBack({ 9, 80, 29, 29 }); // bot
	bot_left.PushBack({ 76, 80, 26, 28 }); // bot left
	left.PushBack({ 9, 117, 30, 27 }); // left
	top_left.PushBack({ 76, 114, 23, 29 }); // top left
	top.PushBack({ 11, 6, 27, 31 }); // top
	top_right.PushBack({ 74, 8, 27, 29 }); // top right
	right.PushBack({ 11, 45, 28, 27 }); // right
	bot_right.PushBack({ 74, 44, 28, 28 }); // bot right

	animation = &bot;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);

	original_point.x = x;
	original_point.x = y;
}

void GreyTurret::Rotate(int player_position_x, int player_position_y)
{
	//while !insiderange
	//define the animation of the turret

	int case_num;
	if (player_position_x == original_point.x && player_position_y > original_point.y)
	{
		animation = &bot;
		case_num = 0;
	}
	else if (player_position_x < original_point.x && player_position_y > original_point.y)
	{
		animation = &bot_left;
		case_num = 1;
	}
	else if (player_position_x < original_point.x && player_position_y == original_point.y)
	{
		animation = &left;
		case_num = 2;
	}
	else if (player_position_x < original_point.x && player_position_y < original_point.y)
	{
		animation = &top_left;
		case_num = 3;
	}
	else if (player_position_x == original_point.x && player_position_y < original_point.y)
	{
		animation = &top;
		case_num = 4;
	}
	else if (player_position_x > original_point.x && player_position_y < original_point.y)
	{
		animation = &top_right;
		case_num = 5;
	}
	else if (player_position_x > original_point.x && player_position_y == original_point.y)
	{
		animation = &right;
		case_num = 6;
	}
	else if (player_position_x > original_point.x && player_position_y > original_point.y)
	{
		animation = &bot_right;
		case_num = 7;
	}
}
