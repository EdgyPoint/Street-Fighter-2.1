#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	//ship
	ship.w = 521;
	ship.h = 182;
	ship.x = 0;
	ship.y = 0;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// gurl animation
	
	gurl.PushBack({ 624, 16, 32, 52 });
	gurl.PushBack({ 624, 80, 32, 52 });
	gurl.PushBack({ 624, 144, 32, 52 });
	gurl.PushBack({ 624, 80, 32, 52 });
	gurl.speed = 0.07f;

	//man couple animation
	man_couple.PushBack({ 552, 8, 64, 64 });
	man_couple.PushBack({ 552, 72, 64, 56 });
	man_couple.PushBack({ 552, 136, 64, 56 });
	man_couple.speed = 0.07f;

	//green boy animation
	green_boy.PushBack({ 664, 16, 32, 56 });
	green_boy.PushBack({ 664, 80, 32, 56 });
	green_boy.speed = 0.07f;

	//blue gabardine animation
	blue_gabardine.PushBack({ 704, 16, 48, 56 });
	blue_gabardine.PushBack({ 704, 80, 48, 56 });
	blue_gabardine.PushBack({ 704, 144, 48, 56 });
	blue_gabardine.speed = 0.07f;

	//orange man animation
	orange_man.PushBack({ 760, 16, 40, 40 });
	orange_man.PushBack({ 760, 64, 40, 40 });
	orange_man.PushBack({ 760, 112, 40, 40 });
	orange_man.speed = 0.07f;

	//pink man animation
	pink_man.PushBack({ 808, 24, 48, 32 });
	pink_man.PushBack({ 808, 72, 48, 32 });
	pink_man.PushBack({ 808, 120, 48, 32 });
	pink_man.speed = 0.07f;


}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->render->Blit(graphics, 0, yship, &ship, 0.75f);
	App->render->Blit(graphics, 192, 104 + yship, &(gurl.GetCurrentFrame()), 0.75f); // gurl animation
	App->render->Blit(graphics, 128, 96 + yship, &(man_couple.GetCurrentFrame()), 0.75f); // man couple animation
	App->render->Blit(graphics, 224, 104 + yship, &(green_boy.GetCurrentFrame()), 0.75f); // green boy animation
	App->render->Blit(graphics, 288, 96 + yship, &(blue_gabardine.GetCurrentFrame()), 0.75f); // blue gabardine animation
	App->render->Blit(graphics, 85, 24 + yship, &(orange_man.GetCurrentFrame()), 0.75f); // orange man animation
	App->render->Blit(graphics, 128, 25 + yship, &(pink_man.GetCurrentFrame()), 0.75f); // orange man animation
	App->render->Blit(graphics, 0, 170, &ground);
	if (frame % 20 == 0)
	{
		if (ship_flag)
		{
			yship++;
			if (yship == 0)
				ship_flag = false;
		}
		else
		{
			yship--;
			if (yship == -4)
				ship_flag = true;
		}
	}
	frame++;

	if (frame == 80)
	{
		frame = 0;
	}
	return UPDATE_CONTINUE;
}