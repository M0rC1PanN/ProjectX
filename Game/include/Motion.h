#pragma once

#include "Main.h"

namespace Motion {
	bool MoveTo(float toX, float toY);
	bool StopMove(float toX, float toY);
	bool Gravity(float& speedf, float& X, float& Y);
	void Jump(float& FLYING, bool& STAY, float& X, float& Y);
}