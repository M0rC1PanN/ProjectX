#include "pch.h"
#include "AgressiveNPC.h"
#include <time.h>
#include "Define.h"
#include "Motion.h"
#include <random>

AgressiveNPC::AgressiveNPC() : Entity() {
	overlook = 10;
	time_of_start = time_of_act = 0;
	check_after_jump = false;
	lastFrameTime = SDL_GetTicks();
	time_of_last_hit = SDL_GetTicks();
	damage = 4;
}

Uint32 AgressiveNPC::getDiff() {
	return SDL_GetTicks() - lastFrameTime;
}

void AgressiveNPC::OnLoop() {
	this->Entity::OnLoop();
	action tmp = Trigger();
	if (tmp != NONE) {
		act = tmp;
	}
	if (SDL_GetTicks() - time_of_start > time_of_act) {
		act = GenerateAction();
		//std::cout << act << '\n';
		switch (act) {
		case CHILL: time_of_start = SDL_GetTicks(), time_of_act = rand() % (second * 4) + 4 * second; break;
		case GO_TO_THE_LEFT: time_of_start = SDL_GetTicks(), time_of_act = rand() % (second * 5) + 5 * second; break;
		case GO_TO_THE_RIGHT: time_of_start = SDL_GetTicks(), time_of_act = rand() % (second * 5) + 5 * second; break;

		default: {
		}
		}
	}

	switch (act) {
	case CHILL: speedr = 0; break;
	case GO_TO_THE_LEFT: speedr = -0.002 * getDiff(); break;
	case GO_TO_THE_RIGHT: speedr = 0.002 * getDiff(); break;
	case HIT: speedr = 0; App::Hero.AddHP(-damage); break;

	default: {

	}
	}
	if (Motion::MoveTo(X + speedr, Y)) {
		X += speedr;
	}
	else {
		if (FLYING < EPS && STAY == true) {
			STAY = false;
			FLYING = 4;
			check_after_jump = true;
			prev_X = X, prev_Y = Y;
		}
		//speedr = 0;
	}
	if (fabs(speedr) > EPS_SPEED) {
		(speedr > 0 ? side = 0 : side = 1);
	}
	//X = round(X * 10) / 10;
	//Y = round(Y * 10) / 10;
	if (FLYING < EPS) {
		if (!Motion::Gravity(speedf, X, Y)) {
			Y = round(Y);
			if (App::Game_Map.MAP[X][Y + 1].TypeID == TILE_TYPE_BLOCK) {
				//X = round(X);
			}
			if (check_after_jump) {
				if (fabs(prev_X - X) < EPS && fabs(prev_Y - Y) < EPS) {
					time_of_act = 0;
				}
				check_after_jump = false;
			}
			STAY = true;
			speedf = 0;
			if (fabs(speedr) > EPS_SPEED) {
				Anim_Control.OnAnimate();
			}
		}
		else {
			STAY = false;
		}
	}
	else {
		Motion::Jump(FLYING, STAY, X, Y);
	}
	lastFrameTime = SDL_GetTicks();
}

action AgressiveNPC::GenerateAction() {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, (int)COUNT - 1);
	return (action)(dis(gen));
}

void AgressiveNPC::OnRender(SDL_Renderer* renderer, float MapX, float MapY) {
	float height = WHEIGHT / TILE_SIZE, weight = WWIDTH / TILE_SIZE;
	float curX = X;
	float curY = Y;
	float X1 = (curX - MapX) * TILE_SIZE;
	float Y1 = (curY - MapY) * TILE_SIZE;
	if ((X >= MapX - 2 || X <= weight + 2) && (Y >= MapY - 2 || Y <= height + 2)) {
		DrawTexture(Texture_Entity, renderer, X1, Y1, AnimState * Width, Anim_Control.GetCurrentFrame() * Height + Height * Anim_Control.MaxFrames * side, Width, Height);
	}
}

action AgressiveNPC::Trigger() {
	for (int i = -overlook; i <= overlook; ++i) {
		for (int j = -overlook; j <= overlook; ++j) {
			int checkX = i + X, checkY = j + Y;
			if ((int)App::Hero.X == checkX && (int)App::Hero.Y == checkY) {
				time_of_act = 1.0;
				time_of_start = SDL_GetTicks();
				int cur_time = SDL_GetTicks();
				if ((int)App::Hero.X == (int)X) {
					if ((int)App::Hero.Y == (int)Y && cur_time - time_of_last_hit > 2 * second) {
						time_of_last_hit = cur_time;
						return HIT;
					}
					else {
						return CHILL;
					}
				}
				if ((int)App::Hero.X < (int)X) {
					return GO_TO_THE_LEFT;
				}
				else {
					return GO_TO_THE_RIGHT;
				}
			}
		}
	}
	return NONE;
}