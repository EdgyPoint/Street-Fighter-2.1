#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 542, 131, 61, 87 });
	backward.PushBack({ 628, 129, 59, 90 });
	backward.PushBack({ 713, 128, 57, 90 });
	backward.PushBack({ 797, 127, 58, 90 });
	backward.PushBack({ 883, 128, 58, 91 });
	backward.PushBack({ 974, 129, 57, 89 });
	backward.speed = 0.1f;

	//Punch animation
	punch.PushBack({ 19, 272, 64, 91 });
	punch.PushBack({ 108, 272, 92, 91 });
	punch.PushBack({ 19, 272, 64, 91 });
	punch.speed = 0.3f;

	//Kick animation
	kick.PushBack({ 607, 268, 59, 94 });
	kick.PushBack({ 689, 267, 66, 92 });
	kick.PushBack({ 777, 265, 114, 94 });
	kick.PushBack({ 689, 267, 66, 92 });
	kick.speed = 0.2f;

	//jump animation
	jump.PushBack({ 20, 847, 55, 85 });
	jump.PushBack({ 100, 823, 56, 104 });
	jump.PushBack({ 176, 805, 50, 89 });
	jump.PushBack({ 251, 798, 54, 77 });
	jump.PushBack({ 327, 813, 48, 70 });
	jump.PushBack({ 397, 810, 48, 89 });
	jump.PushBack({ 464, 819, 55, 109 });
	jump.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if (!punchflag && !kickflag && !jumpflag)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == 1)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == 1)
		{
			current_animation = &backward;
			position.x -= speed;
		}
	}

	if ((App->input->keyboard[SDL_SCANCODE_P] == 1 && punchflag == false) || punchflag == true)
	{
		if (punchcounter <= 10)
		{
			current_animation = &punch;
			punchflag = true;
			punchcounter++;
		}
		else
		{

			if (App->input->keyboard[SDL_SCANCODE_P] == 0)
			{
				punchcounter = 0;
				punchflag = false;
			}
		}
	}

	if ((App->input->keyboard[SDL_SCANCODE_O] == 1 && kickflag == false) || kickflag == true)
	{
		if (kickcounter <= 20)
		{
			current_animation = &kick;
			kickflag = true;
			kickcounter++;
		}
		else
		{

			if (App->input->keyboard[SDL_SCANCODE_O] == 0)
			{
				kickcounter = 0;
				kickflag = false;
			}
		}
	}

	if ((App->input->keyboard[SDL_SCANCODE_W] == 1 && jumpflag == false) || jumpflag == true)
	{
		if (jumpcounter <= 45)
		{
			current_animation = &jump;
			jumpflag = true;
			jumpcounter++;
			if (position.y > 100 && !gravity)
			{
				position.y -= 6;
			}
			else
			{
				gravity = true;
				position.y += 6;
				if (position.y > 220)
				{
					position.y = 220;
				}
			}
		}
		else
		{

			if (App->input->keyboard[SDL_SCANCODE_W] == 0)
			{
				jumpcounter = 0;
				jumpflag = false;
				gravity = false;
			}
		}
	}

	 
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	

	return UPDATE_CONTINUE;
}