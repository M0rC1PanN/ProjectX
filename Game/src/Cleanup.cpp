#include "pch.h"

#include "Main.h"

void App::Cleanup()
{
	for (int i = 0; i < Agr_NPC.size(); ++i) {
		Agr_NPC[i].Entity::OnCleanup();
	}
	for (int i = 0; i < (int)Entity::EntityList.size(); i++) {
		if (!Entity::EntityList[i]) continue;

		Entity::EntityList[i]->OnCleanup();
	}
	Entity::EntityList.clear();
	Hero.OnCleanup();
	App::Game_Map.OnCleanup();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(menu_background);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
