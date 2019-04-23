#include "pch.h"
#include "Interface.h"

void HealthBar::OnRender(SDL_Renderer* renderer) {
	DrawText(renderer, tools.ColorWhite, tools.FontLeadCoat, std::to_string(HP), WWIDTH - 100, 0, 100, 100);
}

void HealthBar::OnLoop(const int _HP) {
	ChangeHP(_HP);
}

MiniMap::MiniMap(std::vector< std::vector<int> >& _map, std::vector< std::vector<int> >& _text) {
	for (int x = 0; x < MAP_WBLOCK; ++x) {
		for (int y = 0; y < MAP_HBLOCK; ++y) {
			map[x][y] = { _map[x][y], _text[x][y] };
		}
	}
}

void MiniMap::OnRender(SDL_Renderer* renderer, float weight, float height) {
	/*float tile_w = MAP_WBLOCK / weight, tile_h = MAP_HBLOCK / height;
	for(float x = 0; x < 
		)*/
}