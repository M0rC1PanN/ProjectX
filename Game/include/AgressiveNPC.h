#pragma once

#include "Entity.h"
#include "Define.h"

enum AgroType {
	ZOMBIE
};

enum action {
	CHILL,
	GO_TO_THE_RIGHT,
	GO_TO_THE_LEFT,
	COUNT,
	NONE,
	HIT,
	JUMP
};

class AgressiveNPC : public Entity{
private:
	Uint32 lastFrameTime;
	AgroType type;
	int overlook;
	action act;
	bool check_after_jump;
	float prev_X, prev_Y;
	int damage;
public:
	AgressiveNPC();
	void OnLoop();
	void OnRender(SDL_Renderer* renderer, partOfDay, float, float);
	virtual action Trigger();
	virtual action GenerateAction();
	Uint32 getDiff();
};
