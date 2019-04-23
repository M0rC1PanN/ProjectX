#include "pch.h"

#include "Main.h"

void App::Loop()
{
	for (int i = 0; i < NUM_AGR_NPC; ++i) {
		Agr_NPC[i].OnLoop();
	
	}
	Game_time.OnLoop();
	CheckFlags();
	Hero.OnLoop();
	HPbar.OnLoop(Hero.HP);
}