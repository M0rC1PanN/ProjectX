#include "pch.h"

#include "Main.h"

Map	App::Game_Map;
MainHero App::Hero;
GameTime App::Game_time;

App::App()
{
	Window = nullptr;
	renderer = nullptr;
	Running = true;
	menu_background = nullptr;

}

int App::StartGame()
{
	if (!Init())
	{
		return -1;
	}

	SDL_Event CurEvent;

	while (Running)
	{
		startTimer();
		while (getDiff() < 1000 / FPS)
		{
			while (SDL_PollEvent(&CurEvent))
			{
				onEvent(&CurEvent);
			}
			if (!flags["ESCAPE"]) {
				if (flags["TAB"]) {
					MinimapRender();
				}
				else {
					Loop();
					Render();
				}
			}
			else if (flags["SETTINGS"]) {
				SettingsRender();
			}
			else {
				MenuRender();
			}

		}
	}

	Cleanup();

	std::cout << "ALL RIGHT\n";
	system("pause");
	return 0;
}

void App::startTimer() {
	timeCounter = SDL_GetTicks();
}

Uint32 App::getDiff() {
	return SDL_GetTicks() - timeCounter;
}

int main(int argc, char* argv[])
{
	App game;

	return game.StartGame();
}