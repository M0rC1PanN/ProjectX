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

	std::array< std::array<Tile, MAP_HBLOCK>, MAP_WBLOCK > MAP;
	SDL_Texture* Tiles_Textures;
	SDL_Texture* backgrounds;

	Map();

	bool OnLoad(std::string File, SDL_Renderer* renderer);

	void OnRender(SDL_Renderer* renderer, float MapX, float MapY);

	void OnCleanup();
};