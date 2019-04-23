#include "pch.h"

#include "Entity.h"
#include "Motion.h"
#include "Define.h"
#include <string>

std::vector<Entity*> Entity::EntityList;

Entity::Entity() {
	Texture_Entity = NULL;

	TypeEntity = KIND_NPC;

	X = Y = 0.0f;
	CAN_JUMP = true;

	Width = Height = 0;
	STAY = true;
	FLYING = speedr = speedf = 0.f;
	time_of_last_damage = time_of_last_add_hp = SDL_GetTicks();

	AnimState = 0;
	side = 0;
}

Entity::~Entity() {
}

bool Entity::OnLoad(std::string File, SDL_Renderer* renderer, int Width, int Height, int MaxFrames) {
	if ((Texture_Entity = LoadImage(File, renderer)) == NULL) {
		return false;
	}

	//Texture::Transparent(Texture_Entity, 255, 0, 255);

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

void Entity::OnLoop() {
	int cur_time = SDL_GetTicks();
	if (cur_time - time_of_last_damage > 15 * second 
		&& cur_time - time_of_last_add_hp > second) {
		AddHP(1);
		time_of_last_add_hp = cur_time;
	}
}

void Entity::AddHP(const int _HP) {
	if (_HP < 0) {
		time_of_last_damage = SDL_GetTicks();
	}
	HP = std::min(MaxHP, HP + _HP);
}

void Entity::OnRender(SDL_Renderer* renderer, partOfDay part) {
	if (Texture_Entity == NULL || renderer == NULL) return;
	DrawTexture(Texture_Entity, renderer, WWIDTH / 2, WHEIGHT / 2, AnimState * Width, Anim_Control.GetCurrentFrame() * Height + Height * Anim_Control.MaxFrames * side, Width, Height, part);
}

void Entity::OnCleanup() {
	if (Texture_Entity) {
		SDL_DestroyTexture(Texture_Entity);
	}

	Texture_Entity = NULL;
}

void Entity::OnMove() {

}