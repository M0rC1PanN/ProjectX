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

class AgressiveNPC : public Entity {
private:
	Uint32 lastFrameTime;
	AgroType type;
	int overlook;
	action act;
	bool check_after_jump;
	float prev_X, prev_Y;
	int damage;
	float speed_param;
	int SeeYou;
public:
	AgressiveNPC();
	void OnLoop();
	void OnRender(SDL_Renderer* renderer, float, float);
	virtual action Trigger();
	virtual action GenerateAction();
	Uint32 getDiff();
};


class Bullet {
public:
	Bullet();
	Bullet(float a, float b, std::pair<float, float> c);
	void OnLoop();
	void OnRender(SDL_Renderer* renderer, float MapX, float MapY);
	float x, y;
	std::pair<float, float> v;
};