#include "pch.h"

#include "Map.h"

Map::Map() {
	Tiles_Textures = backgrounds = nullptr;
	Width = Height = 0;
}

bool Map::OnLoad(std::string File, SDL_Renderer* renderer)
{
	Tiles_Textures = LoadImage("Pictures/MAP_TILES.bmp", renderer);
	if (Tiles_Textures == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	FILE* FileMap = fopen(File.c_str(), "r");

	backgrounds = LoadImage("Pictures/background.bmp", renderer);
	if (backgrounds == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (FileMap == NULL) {
		std::cout << "Can't open File with Map\n";
		return false;
	}

	for (int i = 0; i < MAP_WBLOCK; ++i)
	{
		for (int j = 0; j < MAP_HBLOCK; ++j)
		{
			fscanf(FileMap, "%d:%d ", &MAP[i][j].TextureID, &MAP[i][j].TypeID);
		}
	}

	fclose(FileMap);
	return true;
}

void Map::OnRender(SDL_Renderer* renderer, float MapX, float MapY)
{
	//std::cout << std::setprecision(5) << MapX << ' ' << MapY << '\n';
	for (float X = MapX - 1; X <= MapX + WWIDTH / TILE_SIZE; ++X)
	{
		for (float Y = MapY - 1; Y <= MapY + WHEIGHT / TILE_SIZE; ++Y)
		{
			int curX = X;
			int curY = Y;
			float X1 = (curX - MapX) * TILE_SIZE;
			float Y1 = (curY - MapY) * TILE_SIZE;
			if (curX < MAP_WBLOCK && curY < MAP_HBLOCK && curX >= 0 && curY >= 0 && MAP[curX][curY].TypeID != TILE_TYPE_NONE) {
				if (MAP[curX][curY].TextureID != TILE_TEXT_NONE) {
					float cut_size = 2;
					for (float i = 0; i < cut_size; ++i) {
						for (float j = 0; j < cut_size; ++j) {
							DrawTexture(Tiles_Textures, renderer, X1 + i * TILE_SIZE / cut_size, Y1 + j * TILE_SIZE / cut_size, 0 + i * TILE_SIZE / cut_size, MAP[curX][curY].TextureID * TILE_SIZE + j * TILE_SIZE / cut_size, TILE_SIZE / cut_size, TILE_SIZE / cut_size);
						}
					}
				}
			}
			else {
				float cut_size = 4;
				for (float i = 0; i < cut_size; ++i) {
					for (float j = 0; j < cut_size; ++j) {
						DrawTexture(backgrounds, renderer, X1 + i * TILE_SIZE / cut_size, Y1 + j * TILE_SIZE / cut_size, X1 + i * TILE_SIZE / cut_size, Y1 + j * TILE_SIZE / cut_size, TILE_SIZE / cut_size, TILE_SIZE / cut_size);
					}
				}
			}
		}
	}
}

void Map::OnCleanup()
{
	SDL_DestroyTexture(Tiles_Textures);
}