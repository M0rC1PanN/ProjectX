#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <array>

#include "Tile.h"
#include "Texture.h"

class Map {
public:
	int Width = MAP_WBLOCK;
	int Height = MAP_HBLOCK;
	int radius_of_sight = 10;
	bool at_least_one_block_is_seen = false;
	float minimal_visible_block_x;
	float minimal_visible_block_y;
	float maximal_visible_block_x;
	float maximal_visible_block_y;
	std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK > visible_blocks;
	std::array< std::array<Tile, MAP_HBLOCK>, MAP_WBLOCK > MAP;
	SDL_Texture* Tiles_Textures;
	SDL_Texture* backgrounds;

	Map();
	bool OnLoad(std::string File, SDL_Renderer* renderer);

	void InitializeWithFalse();
	void OnRender(SDL_Renderer* renderer, float MapX, float MapY);
	void MinimapOnRender(SDL_Renderer* renderer);
	void OnCleanup();
};
