#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1b.h"
#include "ModuleLevel1f.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleGameOver.h"
#include "ModuleEnemies.h"

ModuleLevel1b::ModuleLevel1b()
{
	World1 = {0, 0, 256, 4180};
}

ModuleLevel1b::~ModuleLevel1b()
{}

bool ModuleLevel1b::Start()
{
	
	LOG("Loading background assets");
	bool ret = true;
	App->render->camera.y = 0;
	App->particles->Enable();
	wave1 = true;
	wave2 = true;
	wave3 = true;
	wave4 = true;
	wave5 = true;
	wave6 = true;
	wave7 = true;
	wave8 = true;
	wave9 = true;
	wave10 = true;
	wave11 = true;
	wave12 = true;
	wave13 = true;
	wave14 = true;
	wave15 = true;
	wave16 = true;
	wave17 = true;
	wave18 = true;
	wave19 = true;
	wave20 = true;
	wave21 = true;
	wave22 = true;
	wave23 = true;
	wave24 = true;
	wave25 = true;
	wave26 = true;
	wave27 = true;
	wave28 = true;
	wave29 = true; 
	wave30 = true;

	// Background
	graphics = App->textures->Load("Sprites/Maps/map1_base.png");

	// Music
	soundtrack = App->audio->LoadMusic("Audio/Music/Chapter_1.ogg");
	App->audio->PlayMusic1(soundtrack);

	App->collision->Enable();
	App->player->Enable();
	App->scene_level1f->Enable();
	App->enemies->Enable();


	//Boxes
	App->enemies->AddEnemy(ENEMY_TYPES::UPGRADEPOWERUP, 100, 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYPOWERUP, 120, 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEPOWERUP, 140, 100, 0);


	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEBOX, 208, -490, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEBOX, 0, -963, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEBOX, 0, -1497, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEBOX, 200, -2085, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::CHANGEBOX, 200, -3435, 0);

	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYBOX, 200, -530, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYBOX, 85, -1202, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYBOX, 136, -1870, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYBOX, 8, -3148, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::ENERGYBOX, 16, -3435, 0);
	//--------------Grey Turrets----------------------
	
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 3, -577,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 131, -609,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 195, -673,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 131, -993,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 107, -2057,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 43, -2057,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 75, -2018,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 11, -2010,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 147, -2026,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 203, -2002,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 179, -2050,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 155, -2098,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 19, -2098,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 3, -2138,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 75, -2146,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 203, -2130,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 139, -2154,0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYTURRET, 99, -2106,0);
	
	//-----------------Big Turrets-----------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::BIGTURRET, 6, -1330,0);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGTURRET, 165, -1620,0);

	//-----------------Door--------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::DOOR, 73, -3347,0);

	//-----------------Door Turrets--------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::DOORTURRET, 60, -3255,0);
	App->enemies->AddEnemy(ENEMY_TYPES::DOORTURRET, 160, -3255,0);
	
	// Blue destroyed ship
	App->collision->AddCollider({ 0, 56, 16, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -86, 64, 142 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -164, 64, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -141, 25, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -117, 32, 173 }, COLLIDER_WALL);
	App->collision->AddCollider({ 171, -138, 85, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, -86, 95, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 168, -66, 88, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 177, -54, 79, 27 }, COLLIDER_WALL);
	App->collision->AddCollider({ 193, -27, 63, 15 }, COLLIDER_WALL);

	// Columns
	App->collision->AddCollider({ 128, -714, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -779, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -906, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -1065, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 63, -1733, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -1764, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -1796, 32, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 96, -1892, 32, 54 }, COLLIDER_WALL);

	// Defense tower
	App->collision->AddCollider({ 0, -1207, 32, 34 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 0, -1331, 125, 124 }, COLLIDER_TURRET_WALL); // Left Tower
	App->collision->AddCollider({ 0, -1349, 121, 18 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 198, -1351, 58, 145 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 134, -1637, 122, 143 }, COLLIDER_TURRET_WALL); // Right Tower
	App->collision->AddCollider({ 0, -1636, 58, 20 }, COLLIDER_TURRET_WALL);
	App->collision->AddCollider({ 0, -1616, 62, 121 }, COLLIDER_TURRET_WALL); // Pipiru

	//Gate
	App->collision->AddCollider({ 0, -3333, 30, 64 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, -3333, 63, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -3333, 66, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 226, -3333, 30, 64 }, COLLIDER_WALL);

	//Borders

	lborder = App->collision->AddCollider({ -36, -3850, 1, 4180 }, COLLIDER_BORDER);
	rborder = App->collision->AddCollider({ 292, -3850, 1, 4180 }, COLLIDER_BORDER);
	sborder = App->collision->AddCollider({ 300, 300, 1000, 1 }, COLLIDER_BORDER);
	nborder = App->collision->AddCollider({ 0, 0, SCREEN_WIDTH, 20 }, COLLIDER_BORDER_TOP);

	return ret;
}

bool ModuleLevel1b::CleanUp()
{
	LOG("Unloading world1");
	App->textures->Unload(graphics);

	App->collision->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->scene_level1f->Disable();

	return true;
}

update_status ModuleLevel1b::Update()
{
	App->render->Blit(graphics, 0, -3850, &World1, -1.0f, true);

	sborder->SetPos(App->player->position.x - 300, App->player->position.y + 200);
	nborder->SetPos(0, App->render->camera.y / -2);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->player->position.y < -3640 || App->player->destroyed)
	{
		App->fade->FadeToBlack(App->scene_level1b, App->scene_gameover, 2.0);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->player->position.y < -3640 || App->player->destroyed)
	{
		App->fade->FadeToBlack(App->scene_level1b, App->scene_gameover, 2.0);
	}

	if ((App->player->position.y) < 160 && wave1){
		wave1 = false;
		//------------------Soldiers----------------------
		//1 = L right, 2 = Vertical, 3 = stay, 4 = L left, 5= horizontal
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 140, -40, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 10, -340, 3);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUESOLDIER, 20 ,100,3);
	}

	if ((App->player->position.y) < 135 && wave2){
		wave2 = false;
		//1 = L right, 2 = Vertical, 3 = stay, 4 = L left, 5= horizontal
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 100, -80, 1);
	}

	if ((App->player->position.y) < 70 && wave3){
		wave3 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 125, -180, 1);
	}

	if ((App->player->position.y) < 30 && wave4){
		wave4 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 95, -180, 2);
	}
	if ((App->player->position.y) < -15 && wave5){
		wave5 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 135, -200, 2);
	}
	if ((App->player->position.y) < -55 && wave6){
		wave6 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 110, -250, 2);
	}
	if ((App->player->position.y) < -85 && wave7){
		wave7 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 95, -280, 2);
	}
	if ((App->player->position.y) < -130 && wave8){
		wave8 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 150, -430, 1);
	}
	if ((App->player->position.y) < -160 && wave9){
		wave9 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 125, -450, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 185, -440, 1);

	}
	if ((App->player->position.y) < -220 && wave10){
		wave10 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -480, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 110, -450, 1);

	}
	if ((App->player->position.y) < -240 && wave11){
		wave11 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 40, -470, 1);
	}
	if ((App->player->position.y) < -250 && wave12){
		wave12 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 185, -480, 4);
		App->enemies->AddEnemy(ENEMY_TYPES::REDSOLDIER, 90, -490, 4);//red soldier
	}
	if ((App->player->position.y) < -320 && wave13){
		wave13 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 160, -590, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 120, -590, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 85, -630, 1);
	}
	if ((App->player->position.y) < -340 && wave14){
		wave14 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 130, -530, 4);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 100, -530, 4);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 75, -550, 4);
	}
	if ((App->player->position.y) < -440 && wave15){
		wave15 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -630, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 30, -620, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 15, -660, 1);
	}
	//the ones that come from out of the truck
	if ((App->player->position.y) < -440 && wave15){
		wave15 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -630, 9);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -620, 9);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -660, 9);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -620, 9);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -660, 9);
	}
	if ((App->player->position.y) < -900 && wave16){
		wave16 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 240, -1150, 6);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 60, -1150, 10);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1170, 10);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 40, -1200, 10);
	}
	if ((App->player->position.y) < -920 && wave17){
		wave17 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 260, -1180, 6);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 240, -1120, 6);
	}
	if ((App->player->position.y) < -1060 && wave18){
		wave18 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 120, -1300, 1);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 160, -1310, 1);
	}
	if ((App->player->position.y) < -1115 && wave19){
		wave19 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 115, -1350, 11);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 165, -1350, 11);
	}
	if ((App->player->position.y) < -1130 && wave20){
		wave20 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 110, -1400, 11);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 165, -1400, 11);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 130, -1380, 11);

	}
	//-----------between big turrets horizontals
	if ((App->player->position.y) < -1130 && wave23){
		wave23 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 15, -1450, 13);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 50, -1450, 13);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 85, -1450, 13);
		App->enemies->AddEnemy(ENEMY_TYPES::REDSOLDIER, 120, -1450, 13);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 155, -1450, 13);
	}


	if ((App->player->position.y) < -1130 && wave22){
		wave22 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 10, -1420, 12);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 45, -1420, 12);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1420, 12);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 115, -1420, 12);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 150, -1420, 12);
	}

	if ((App->player->position.y) < -1130 && wave21){
		wave21 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 0, -1390, 5);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 35, -1390, 5);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 70, -1390, 5);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 105, -1390, 5);
	}
	//-----------between big turrets horizontals

	if ((App->player->position.y) < -1320 && wave24){
		wave24 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 50, -1560, 14);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 100, -1550, 14);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 70, -1540, 14);

	}
	//diagonals
	if ((App->player->position.y) < -1450 && wave25){
		wave25 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::REDSOLDIER, 50, -1620, 15);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 75, -1640, 15);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 100, -1660, 15);

	}
	if ((App->player->position.y) < -1480 && wave26){
		wave26 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 50, -1670, 5);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 85, -1670, 5);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 120, -1670, 5);
	}

	if ((App->player->position.y) < -1520 && wave27){
		wave27 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 0, -1710, 16);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 30, -1710, 16);
	}

	if ((App->player->position.y) < -1650 && wave28){
		wave28 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 15, -1800, 17);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1810, 20);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 180, -1830, 19);
	}


	if ((App->player->position.y) < -1665 && wave29){
		wave29 = false;
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 15, -1835, 17);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1835, 20);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 180, -1825, 18);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1870, 20);


	}

	if ((App->player->position.y) < -1650 && wave30){
		wave30 = false;

		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 15, -1860, 17);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 80, -1910, 20);
		App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER1, 190, -1880, 19);

	}



	return UPDATE_CONTINUE;
}