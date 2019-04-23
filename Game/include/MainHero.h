#pragma once

#include <SDL.h>

#include "Entity.h"

class MainHero : public Entity{
public:
	MainHero();
	void OnLoop();
	void SetVisionRadius(float radius);
	float GetVisionRadius();
	void SetBlackoutLevel(float level);
	float GetBlackoutLevel();
private:
	float vision_radius;
	float blackout_level;
};