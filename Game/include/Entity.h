#pragma once

#include <vector>
#include <string>

#include "Animation.h"
#include "Texture.h"

enum type {
	PLAYER,
	ANGRY_NPC,
	KIND_NPC
};

class Entity {
public:
	static std::vector<Entity*>    EntityList;

protected:
	Animation		Anim_Control;

	SDL_Texture*    Texture_Entity;

public:
	float           X;
	float           Y;

	int             Width;
	int             Height;
	
	int				side;
	int             AnimState;
	type			TypeEntity;

	float			FLYING;
	float			speedr;
	float			speedf;
	bool			STAY;
	bool			CAN_JUMP;

	int				HP, MaxHP;
	int				time_of_last_damage;
	int				time_of_last_add_hp;
	int				time_of_act;
	int				time_of_start;
	int				time_of_last_hit;

public:
	Entity();

	virtual ~Entity();

public:
	virtual bool OnLoad(std::string File, SDL_Renderer* renderer, int Width, int Height, int MaxFrames);

	virtual void OnLoop();

	virtual void OnRender(SDL_Renderer* renderer, partOfDay part);

	virtual void OnCleanup();

	virtual void OnMove();

	virtual void AddHP(const int);
};