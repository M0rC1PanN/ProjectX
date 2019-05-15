#include "pch.h"

#include "Main.h"

void App::Loop()
{
	for (int i = 0; i < (int)Agr_NPC.size(); ++i) {
		Agr_NPC[i].OnLoop();

	}
	std::cout << Bullets.size() << '\n';
	for (int i = 0; i < Bullets.size(); ++i) {
		Bullets[i].OnLoop();
	}
	for (int i = 0; i < Bullets.size(); ++i) {
		for (int j = 0; j < (int)Agr_NPC.size(); ++j) {
			if ((int)Bullets[i].x == (int)Agr_NPC[j].X && (int)Bullets[i].y == (int)Agr_NPC[j].Y ||
				(int)Bullets[i].x == (int)Agr_NPC[j].X && (int)Bullets[i].y == (int)Agr_NPC[j].Y + 1) {
				Agr_NPC[j].AddHP(-(rand() % 10 + 10)*(4 * (rand() % 5 == 4) + 1));
				Bullets[i].x = 9999999;
			}
		}
	}
	for (int i = (int)Agr_NPC.size() - 1; i >= 0; --i) {
		if (Agr_NPC[i].dead == true) {
			Agr_NPC.erase(Agr_NPC.begin() + i);
		}
	}
	Game_time.OnLoop();
	CheckFlags();
	Hero.OnLoop();
	HPbar.OnLoop(Hero.HP);
}

void App::MenuLoop() {

}