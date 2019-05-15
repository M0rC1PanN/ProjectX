#include "pch.h"

#include "Main.h"

void App::Render()
{
	SDL_RenderClear(renderer);

	float tmpX = WWIDTH / TILE_SIZE / 2, tmpY = WHEIGHT / TILE_SIZE / 2;

	Camera::CameraControl.SetPos(Hero.X - tmpX, Hero.Y - tmpY);
	App::Game_Map.OnRender(renderer, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());

	for (int i = 0; i < NUM_AGR_NPC; ++i) {
		Agr_NPC[i].OnRender(renderer, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
	}

	Hero.OnRender(renderer, Game_time.GetPart());
	HPbar.OnRender(renderer);
	if (Hero.HP <= 0) {
		Running = 0;
		SDL_Texture* you_died = LoadImage("Pictures/you_died.bmp", renderer);
		DrawTexture(you_died, renderer, 0, 0, 0, 0, WWIDTH, WHEIGHT);
		SDL_DestroyTexture(you_died);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}
	
	SDL_RenderPresent(renderer);
	SDL_Delay(1);
}

void App::MenuRender() {
	SDL_RenderClear(renderer);
	DrawTexture(menu_background, renderer, 100, 100, 0, 0, background_width, background_height);
	for (int i = 0; i < 4; ++i) {
		DrawTexture(menu_buttons, renderer, 
			WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + i*BYDELTA,
			0, i * BHEIGHT, 
			BWIDTH, BHEIGHT);
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1);
}

void App::MinimapRender() {
	SDL_RenderClear(renderer);
	Game_Map.MinimapOnRender(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1);
}

void App::SettingsRender() {
	SDL_RenderClear(renderer);
	DrawTexture(menu_background, renderer, 100, 100, 0, 0, background_width, background_height);
	DrawTexture(menu_buttons, renderer,
				WWIDTH / 2 - 100, WHEIGHT / 2 - 300,
				illumination * BWIDTH, 4 * BHEIGHT,
				BWIDTH, BHEIGHT);
	DrawTexture(menu_buttons, renderer,
		WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + BYDELTA,
		complexity * BWIDTH, 5 * BHEIGHT,
		BWIDTH, BHEIGHT);
	DrawTexture(menu_buttons, renderer,
		WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + 2*BYDELTA,
		0, 6 * BHEIGHT,
		BWIDTH, BHEIGHT);
;	SDL_RenderPresent(renderer);
	SDL_Delay(1);
}