#include "pch.h"

#include <iostream>
#include <fstream>
#include "Main.h"
#include <random>
#include <array>

int dx[8] = { 1, 1, 1,-1, -1,-1, 0, 0 };
int dy[8] = { 0,-1, 1, 0, -1, 1, 1,-1 };

enum direction {
	UP,
	DOWN,
	STRAIGHT,
	COUNT_
};

int App::countAliveNeighbours(int &x, int &y, const std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK>& type) {
	int count = 0;
	for (int i = 0; i < 8; ++i) {
		int cx = x + dx[i], cy = y + dy[i];
		if (cx >= MAP_WBLOCK || cy >= MAP_HBLOCK || cy < 0 || cx < 0) {
			count++;
		}
		else {
			if (type[cx][cy] == TILE_TYPE_BLOCK) {
				count++;
			}
		}
	}

	return count;
}

void App::doSimulationStep(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK>& type, const int& deathLimit, const int& birthLimit,
	const std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change) {
	std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK> new_type = { TILE_TYPE_NONE };
	for (int x = 0; x < MAP_WBLOCK; ++x) {
		for (int y = 0; y < MAP_HBLOCK; ++y) {
			if (!do_not_change[x][y]) {
				int cnt = countAliveNeighbours(x, y, type);
				if (type[x][y] == TILE_TYPE_BLOCK) {
					if (cnt < deathLimit) {
						new_type[x][y] = TILE_TYPE_NONE;
					}
					else {
						new_type[x][y] = TILE_TYPE_BLOCK;
					}
				}
				else {
					if (cnt > birthLimit) {
						new_type[x][y] = TILE_TYPE_BLOCK;
					}
					else {
						new_type[x][y] = TILE_TYPE_NONE;
					}
				}
			}
		}
	}
	type = std::move(new_type);
}

void App::GenerateRandomCaveLevel(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK >& type, std::array< std::array<Tile_text, MAP_HBLOCK>, MAP_WBLOCK >& text,
	const std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change) {
	const int chanceToStartAlive = 50; // %
	const int simulationSteps = 100;
	const int deathLimit = 4;
	const int birthLimit = 4;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	for (int x = 0; x < MAP_WBLOCK; ++x) {
		for (int y = 0; y < MAP_HBLOCK; ++y) {
			if (!do_not_change[x][y]) {
				if (dis(gen) <= chanceToStartAlive) {
					type[x][y] = TILE_TYPE_BLOCK;
				}
				else {
					type[x][y] = TILE_TYPE_NONE;
				}
			}
		}
	}

	for (int i = 0; i < simulationSteps; ++i) {
		SDL_RenderClear(renderer);

		std::string text = "Creation   of   map   ";
		text += std::to_string((100 / simulationSteps) * (i + 1));
		text += "%";
		DrawText(renderer, tools.ColorBlack, tools.Graph_35_pix, text, WWIDTH / 2 - 500, WHEIGHT / 2 - 200, 1200, 150);
		SDL_RenderPresent(renderer);
		//std::cout << "Creation of map " << i + 1 << "%\n";
		doSimulationStep(type, deathLimit, birthLimit, do_not_change);
	}
}

void App::GenerateHills(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK >& type,
	std::array< std::array<Tile_text, MAP_HBLOCK>, MAP_WBLOCK >& text,
	std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change) {
	int cur_x = 0, cur_y = surface_level - 10, repeat, height, length, small_height;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> act_gen(0, COUNT_ - 1);
	std::uniform_int_distribution<> repeat_gen(4, 10);
	std::uniform_int_distribution<> height_gen(8, 15);
	std::uniform_int_distribution<> length_gen(1, 3);
	std::uniform_int_distribution<> small_height_gen(1, 3);

	while (cur_x < MAP_WBLOCK) {
		direction action_ = (direction)act_gen(gen);
		switch (action_) {
		case STRAIGHT: {
			height = 0;
			repeat = repeat_gen(gen);
			int bound = std::min(cur_x + repeat, MAP_WBLOCK - 1);
			for (cur_x; cur_x <= bound; cur_x++) {
				for (int y = cur_y; y < surface_level; y++) {
					type[cur_x][y] = TILE_TYPE_BLOCK;
				}
				for (int y = 0; y < cur_y + 10; y++) {
					do_not_change[cur_x][y] = true;
				}
			}
			break;
		}
		case UP: {
			height = std::max(5, -1 * height_gen(gen) + cur_y);
			while (cur_y != height && cur_x <= MAP_WBLOCK - 1) {
				length = std::min(length_gen(gen), MAP_WBLOCK - 1 - cur_x);
				int bound = cur_x + length;
				for (cur_x; cur_x <= bound; cur_x++) {
					for (int y = cur_y; y < surface_level; y++) {
						type[cur_x][y] = TILE_TYPE_BLOCK;
					}
					for (int y = 0; y < cur_y + 10; y++) {
						do_not_change[cur_x][y] = true;
					}
				}
				cur_y = std::max(cur_y - small_height_gen(gen), height);
			}
			break;
		}
		case DOWN: {
			height = std::min(surface_level, cur_y + height_gen(gen));
			while (cur_y != height && cur_x <= MAP_WBLOCK - 1) {
				length = std::min(length_gen(gen), MAP_WBLOCK - 1 - cur_x);
				int bound = cur_x + length;
				for (cur_x; cur_x <= bound; cur_x++) {
					for (int y = cur_y; y < surface_level; y++) {
						type[cur_x][y] = TILE_TYPE_BLOCK;
					}
					for (int y = 0; y < cur_y + 10; y++) {
						do_not_change[cur_x][y] = true;
					}
				}
				cur_y = std::min(cur_y + small_height_gen(gen), height);
			}
			break;
		}
		}
	}

}

void App::Generator()
{
	FILE *kek = fopen("Maps/1.map", "w");

	static std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK > type = { TILE_TYPE_NONE };
	static std::array< std::array<Tile_text, MAP_HBLOCK>, MAP_WBLOCK > text = { TILE_TEXT_NONE };
	static std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK> do_not_change = { false };

	//for (int x = 0; x < MAP_WBLOCK; ++x) {
	//	for (int y = surface_level; y <= surface_level + 10; ++y) {
	//		type[y][x] = 
	//	}
	//}

	GenerateHills(type, text, do_not_change);
	GenerateRandomCaveLevel(type, text, do_not_change);
	for (int x = 0; x < MAP_WBLOCK; ++x) {
		for (int y = 0; y < MAP_HBLOCK; ++y) {
			/////////////////////////////////////
			if (x == 0 || x == MAP_WBLOCK - 1) {
				type[x][y] = TILE_TYPE_BLOCK;
			}
			/////////////////////////////////////
			if (type[x][y] == TILE_TYPE_BLOCK) {
				text[x][y] = TILE_TEXT_BRICK;
			}
			else {
				text[x][y] = TILE_TEXT_NONE;
			}
		}
	}

	for (int i = 0; i < MAP_WBLOCK; ++i) {
		for (int j = 0; j < MAP_HBLOCK; ++j) {
			fprintf(kek, "%d:%d ", text[i][j], type[i][j]);
		}
		fprintf(kek, "\n");
	}
	fclose(kek);
}
