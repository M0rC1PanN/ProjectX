#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include <map>

#include "Define.h"
#include "Texture.h"
#include "Events.h"
#include "Animation.h"
#include "Entity.h"
#include "Camera.h"
#include "Map.h"
#include "MainHero.h"
#include "Motion.h"
#include "AgressiveNPC.h"
#include "Instruments.h"
#include "Interface.h"
#include "GameTime.h"

class App : public Events{
private:
	std::vector<AgressiveNPC>			Agr_NPC;
private:
	Animation							Anim_Yoshi;
	bool Running;
	int timeCounter;
	int background_width, background_height;
	SDL_Surface*						ScreenSurface;
	SDL_Window*							Window;
	SDL_Texture*						menu_background;
	SDL_Texture*						menu_buttons;
	SDL_Renderer*						renderer;
	std::map < std::string, bool >		flags;
	Instruments							tools;
	HealthBar							HPbar;
public:
	static Map							Game_Map;
	static MainHero						Hero;
	static GameTime						Game_time;

	int illumination = 0;
	int complexity = 0;
public:
	App();
	~App() {};
	bool Init(); // Ду
	void onEvent(SDL_Event* Event); // Функция, отвечаеющая на действие игрока
	void Loop(); // Подготавливает данные для рендеринга, после какого-то ивента(обновляет ХП, местоположение мобов)
	void Render(); // Из названия понятно
	void MenuRender();
	void MinimapRender();
	void SettingsRender();
	void OnExit(); // Выйди и зайди нормально
	void Generator(); // Генератор ы
	void OnKeyDown(SDL_Keycode sym, int mod, int unicode);
	void OnKeyUp(SDL_Keycode sym, int mod, int unicode);
	void OnLButtonUp(int mX, int mY);
	void OnLButtonDown(int mX, int mY);
	void Cleanup(); // Очистить все, что мы загрузили(изображения, карты и тд и тп)
	int StartGame(); // Покажите мне дауна, который не поймет, что здесь написано
	void CheckFlags();
	void startTimer();
	Uint32 getDiff();
	void MenuLoop();
public:
	int countAliveNeighbours(int &x, int &y, const std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK>& type);
	void doSimulationStep(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK>& type, const int& deathLimit, const int& birthLimit, const std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change);
	void GenerateRandomCaveLevel(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK >& type, std::array< std::array<Tile_text, MAP_HBLOCK>, MAP_WBLOCK >& text,
		const std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change);
	void GenerateHills(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK >& type, std::array< std::array<Tile_text, MAP_HBLOCK>, MAP_WBLOCK >& text,
		std::array< std::array<bool, MAP_HBLOCK>, MAP_WBLOCK>& do_not_change);
	void DeleteHoles(std::array< std::array<Tile_type, MAP_HBLOCK>, MAP_WBLOCK >& type);
};