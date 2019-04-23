//Этот класс нам нужен для анимирования Сущности(Entity)
//Краткое описание: в зависимости от времени воспроизводится какой-либо кадр

#pragma once

#include <SDL.h>

class Animation {
private:
	int    CurrentFrame;

	int     FrameInc;

	int     FrameRate; //Milliseconds

	long    OldTime;

public:
	int    MaxFrames;

	bool    Oscillate;

	Animation();

	void OnAnimate();

	void SetFrameRate(int Rate);

	void SetCurrentFrame(int Frame);

	int GetCurrentFrame();
};
