#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class Instruments {
public:
	TTF_Font* FontLeadCoat;
	TTF_Font* TheJewishBitmap;
	TTF_Font* Hobby_of_night;
	TTF_Font* Graph_35_pix;
	SDL_Color ColorWhite, ColorBlack;
	Instruments() {
		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
		}
		FontLeadCoat = TTF_OpenFont("Pictures/leadcoat.ttf", 24);
		if (!FontLeadCoat) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		TheJewishBitmap = TTF_OpenFont("Pictures/TheJewishBitmap.ttf", 24);
		if (!TheJewishBitmap) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		Graph_35_pix = TTF_OpenFont("Pictures/Graph-35-pix.ttf", 24);
		if (!Graph_35_pix) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		Hobby_of_night = TTF_OpenFont("Pictures/Hobby_of_night.ttf", 24);
		if (!Hobby_of_night) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		ColorWhite = { 255, 255, 255 };
		ColorBlack = { 255, 0, 0 };
	}
	void OnCleanup() {
	};
};