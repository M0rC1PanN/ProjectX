#pragma once

#include "Instruments.h"
#include "Texture.h"
#include "Define.h"
#include <vector>

class HealthBar {
private:
	int HP;
	Instruments tools;
public:

	HealthBar() { HP = 100; };

	void ChangeHP(int _HP) {
		HP = _HP;
	};

	void OnLoop(const int);
	void OnRender(SDL_Renderer* renderer);
	void OnCleanup();
};

struct MiniMap {
	std::pair<int, int> map[MAP_WBLOCK][MAP_HBLOCK];
	MiniMap() {};
	MiniMap(std::vector< std::vector<int> >& _map, std::vector< std::vector<int> >& _text);
	void OnRender(SDL_Renderer*, float, float);
};