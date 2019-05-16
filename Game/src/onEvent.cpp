#include "pch.h"

#include "Main.h"

void App::onEvent(SDL_Event* Event)
{
	Events::OnEvent(Event);
}

void App::OnExit() {
	Running = false;
}

void App::OnLButtonUp(int mX, int mY) {
	if (flags["SETTINGS"]) {
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 && mY <= WHEIGHT / 2 - 300 + BHEIGHT) {
			SDL_Delay(100);
			illumination = (illumination + 1) % 2;

		}
		else if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + BYDELTA && mY <= WHEIGHT / 2 - 300 + BHEIGHT + BYDELTA) {
			SDL_Delay(100);
			complexity = (complexity + 1) % 4;

		}
		else if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + 2 * BYDELTA &&
			mY <= WHEIGHT / 2 - 300 + BHEIGHT + 2 * BYDELTA) {
			SDL_Delay(100);
			flags["SETTINGS"] = false;
		}
	}
	else if (flags["ESCAPE"]) {
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 && mY <= WHEIGHT / 2 - 300 + BHEIGHT) {
			SDL_Delay(100);
			Generator();
			App::Game_Map.OnLoad("Maps/1.map", renderer);
			Hero.X = 5, Hero.Y = 4;
			flags["ESCAPE"] = false;
		}
		else if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + BYDELTA && mY <= WHEIGHT / 2 - 300 + BHEIGHT + BYDELTA) {
			SDL_Delay(100);
			flags["ESCAPE"] = false;
		}
		else if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + 2 * BYDELTA &&
			mY <= WHEIGHT / 2 - 300 + BHEIGHT + 2 * BYDELTA) {
			SDL_Delay(100);
			flags["SETTINGS"] = true;
		}
		else if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + 3 * BYDELTA &&
			mY <= WHEIGHT / 2 - 300 + BHEIGHT + 3 * BYDELTA) {
			SDL_Delay(100);
			Running = 0;
		}
		return;
	}
}

void App::OnLButtonDown(int mX, int mY) {
	if (flags["SETTINGS"]) {

	}
	else
	if (flags["ESCAPE"]) {
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 && mY <= WHEIGHT / 2 - 300 + BHEIGHT) {
			DrawTexture(menu_buttons, renderer,
				WWIDTH / 2 - 100, WHEIGHT / 2 - 300,
				BWIDTH, 0,
				BWIDTH, BHEIGHT);
		}
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + BYDELTA && mY <= WHEIGHT / 2 - 300 + BHEIGHT + BYDELTA) {
			DrawTexture(menu_buttons, renderer,
				WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + BYDELTA,
				BWIDTH, BHEIGHT,
				BWIDTH, BHEIGHT);
		}
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + 2 * BYDELTA &&
			mY <= WHEIGHT / 2 - 300 + BHEIGHT + 2 * BYDELTA) {
			DrawTexture(menu_buttons, renderer,
				WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + 2 * BYDELTA,
				BWIDTH, 2 * BHEIGHT,
				BWIDTH, BHEIGHT);
		}
		if (mX >= WWIDTH / 2 - 100 && mX <= WWIDTH / 2 - 100 + BWIDTH
			&& mY >= WHEIGHT / 2 - 300 + 3 * BYDELTA &&
			mY <= WHEIGHT / 2 - 300 + BHEIGHT + 3 * BYDELTA) {
			DrawTexture(menu_buttons, renderer,
				WWIDTH / 2 - 100, WHEIGHT / 2 - 300 + 3 * BYDELTA,
				BWIDTH, 3 * BHEIGHT,
				BWIDTH, BHEIGHT);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(500);
		return;
	}
	
	int x = round(Camera::CameraControl.GetX()) + mX / TILE_SIZE, y = round(Camera::CameraControl.GetY()) + mY / TILE_SIZE;
	if (mode == DigMode) {
		if (fabs(Hero.X - x) <= 2 && fabs(Hero.Y - y) <= 2 &&
			x >= 0 && x < MAP_WBLOCK && y >= 0 && y < MAP_HBLOCK &&
			Game_Map.MAP[x][y].TypeID == TILE_TYPE_BLOCK) {
			Game_Map.MAP[x][y].TypeID = TILE_TYPE_NONE;
			Game_Map.MAP[x][y].TextureID = TILE_TEXT_NONE;
		}
	}
	else if (mode == FightMode) {
		float length = sqrt((y - App::Hero.Y)*(y - App::Hero.Y) + (x - App::Hero.X)*(x - App::Hero.X));
		Bullets.push_back(Bullet(App::Hero.X, App::Hero.Y, { (x - App::Hero.X) / length , (y - App::Hero.Y) / length }));
	}
}

void App::OnKeyDown(SDL_Keycode sym, int mod, int unicode){
		switch (sym) {
			//case SDLK_UP:    if (Motion::MoveTo(Hero.X, Hero.Y - 1)) Hero.Y -= STEP; break;
			//case SDLK_DOWN:  if (Motion::MoveTo(Hero.X, Hero.Y + 1)) Hero.Y += STEP; break;
		case SDLK_a:		flags["A"] = true; break;
		case SDLK_d:		flags["D"] = true; break;
		case SDLK_SPACE:	flags["SPACE"] = true; break;
		case SDLK_ESCAPE:	flags["ESCAPE"] ^= true; break;
		case SDLK_TAB:		flags["TAB"] ^= true; break;
		case SDLK_1:		mode = FightMode; break;
		case SDLK_2:		mode = DigMode;	break;
		default: {
		}
		}
}

void App::OnKeyUp(SDL_Keycode sym, int mod, int unicode) {
		switch (sym) {
		case SDLK_a:		flags["A"] = false; Hero.speedr = 0; break;
		case SDLK_d:		flags["D"] = false; Hero.speedr = 0; break;
		case SDLK_SPACE:	flags["SPACE"] = false; Hero.CAN_JUMP = true; break;

		default: {
		}
		}
}

void App::CheckFlags() {
	if (flags["A"] == true) {
		Hero.speedr -= STEP; Hero.speedr = std::max(-STEP * 1.0, 1.0 * Hero.speedr);
	}
	if (flags["D"] == true) {
		Hero.speedr += STEP; Hero.speedr = std::min(STEP * 1.0, 1.0 * Hero.speedr);
	}
	if (flags["SPACE"] == true) {
		if (Hero.STAY && Hero.CAN_JUMP) {
			Hero.FLYING = jump, Hero.CAN_JUMP = false;
		}
	}
}