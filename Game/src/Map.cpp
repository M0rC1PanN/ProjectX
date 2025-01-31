#include "pch.h"

#include "Map.h"
#include "Main.h"

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
					if (!at_least_one_block_is_seen) {
						minimal_visible_block_x = X;
						minimal_visible_block_y = Y;
						maximal_visible_block_x = X;
						maximal_visible_block_y = Y;
						visible_blocks[X][Y] = true;
						at_least_one_block_is_seen = true;
					}
					else {
						minimal_visible_block_x = std::min(std::max(X, App::Hero.X - 960 / 5), minimal_visible_block_x);
						minimal_visible_block_y = std::min(std::max(Y, App::Hero.Y - 540 / 5), minimal_visible_block_y);
						maximal_visible_block_x = std::max(std::min(X, App::Hero.X + 960 / 5), maximal_visible_block_x);
						maximal_visible_block_y = std::max(std::min(Y, App::Hero.Y + 540 / 5), maximal_visible_block_y);
						visible_blocks[X][Y] = true;

					}
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

void Map::InitializeWithFalse() {
	for (int i = 0; i < MAP_WBLOCK; i++) {
		for (int j = 0; j < MAP_HBLOCK; j++) {
			visible_blocks[i][j] = false;
		}
	}
}


void Map::MinimapOnRender(SDL_Renderer* renderer) {
	float X = (maximal_visible_block_x + minimal_visible_block_x) / 2;
	float Y = (minimal_visible_block_y + maximal_visible_block_y) / 2;
	float tmp_x = 1;
	float one_more_tmp_x = MAP_WBLOCK - 1;
	for (float x = std::max(minimal_visible_block_x, tmp_x); x < std::min(one_more_tmp_x, maximal_visible_block_x); x++) {
		for (float y = minimal_visible_block_y; y < maximal_visible_block_y; y++) {
			if (visible_blocks[x][y] && App::Game_Map.MAP[x][y].TypeID == TILE_TYPE_BLOCK) {
				DrawTexture(Tiles_Textures, renderer, 960 - (X - x) * 5, 540 - (Y - y) * 5, 3, 3, 5, 5);
				//DrawTexture(menu_background, renderer, 300, 100, 0, 0, backgrou nd_width, background_height);
			}
		}
	}
	SDL_Texture* pers = LoadImage("Pictures/Green.bmp", renderer);
	DrawTexture(pers, renderer, 960 - (X - App::Hero.X) * 5 - 10, 540 - (Y - App::Hero.Y) * 5 - 10, 3, 3, 20, 20);
	SDL_DestroyTexture(pers);
}