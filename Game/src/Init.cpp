#include "pch.h"

#include "Main.h"

bool App::Init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR: " << SDL_GetError() << "\n";
		return false;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		return false;
	}

	Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
	if (Window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	/*Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);*/ /// FOR FULLSCREEN
	
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}


	//Generator();

	background = LoadImage("Pictures/background.bmp", renderer);
	if (background == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (Hero.OnLoad("Pictures/yoshi.bmp", renderer, EntityWidht, EntityHeight, 8) == false) {
		return false;
	}

	Hero.X = 5, Hero.Y = 4;

	Agr_NPC.resize(NUM_AGR_NPC);
	for (int i = 0; i < NUM_AGR_NPC; ++i) {
		Agr_NPC[i].X = rand() % (MAP_WBLOCK - 200) + 100, Agr_NPC[i].Y = 0;
		if(Agr_NPC[i].OnLoad("Pictures/zombie.bmp", renderer, EntityWidht, EntityHeight, 1) == false){
			return false;
		}
	}

	App::Game_Map.OnLoad("Maps/1.map", renderer);

	return true;
}