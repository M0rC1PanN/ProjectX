#include "pch.h"

#include "Motion.h"

bool Motion::MoveTo(float toX, float toY) {
	if (StopMove(toX, toY)) {
		return false;
	}
	return true;
}

bool Motion::StopMove(float toX, float toY) {
	//std::cout << std::fixed << std::setprecision(5) << "toX = " << toX << ' ' << "  toY = " << toY << '\n';
	float X = toX, Y = toY;
	toX = (int)(fabs(toX - (int)toX) < EPS ? toX : ceil(toX));
	toY = (int)(fabs(toY - (int)toY) < EPS ? toY : ceil(toY));
	//std::cout << "X = " << toX << ' ' << "  Y = " << toY << '\n';
	if ((int)toX >= 0 && (int)toX < MAP_WBLOCK && (int)toY >= 0 && (int)toY < MAP_HBLOCK 
		&& (App::Game_Map.MAP[(int)toX][(int)toY].TypeID == TILE_TYPE_BLOCK 
		|| App::Game_Map.MAP[(int)X][(int)Y].TypeID == TILE_TYPE_BLOCK
		|| ((int)Y + 1 >= MAP_HBLOCK || App::Game_Map.MAP[(int)X][(int)Y + 1].TypeID == TILE_TYPE_BLOCK)
		|| ((int)toY + 1 >= MAP_HBLOCK || App::Game_Map.MAP[(int)toX][(int)toY+1].TypeID == TILE_TYPE_BLOCK))) {
		return true;
	}
	return false;
}

bool Motion::Gravity(float& speedf, float& X, float& Y) {
	float X1 = (int)(fabs(X - (int)X) < EPS ? X : ceil(X));
	//std::cout << std::fixed << std::setprecision(5) << "Gravity: " << X << ' ' << Y << '\n';
	if (X1 < 0 || X > MAP_WBLOCK || (Y + speedf) > MAP_HBLOCK
		|| fabs(X - MAP_WBLOCK) < EPS || fabs((Y + speedf) - MAP_HBLOCK) < EPS
		|| (App::Game_Map.MAP[abs((int)X)][(int)(Y + speedf)+2].TypeID != TILE_TYPE_BLOCK
		&& App::Game_Map.MAP[X1][(int)(Y + speedf) +2].TypeID != TILE_TYPE_BLOCK)) {
		Y += speedf;
		speedf = std::min(0.5, 1.0 * speedf + STEP / 10);
		return true;
	}
	return false;
}

void Motion::Jump(float& FLYING, bool& STAY, float& X, float& Y) {
	if (FLYING < EPS) {
		FLYING = 0;
		return;
	}
	if (MoveTo(X, Y - STEP)) {
		STAY = false;
		Y -= STEP;
		FLYING -= STEP;
	}
	else {
		FLYING = 0;
	}
}