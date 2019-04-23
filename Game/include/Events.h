#pragma once

#include <SDL.h>

class Events {
public:
	SDL_Event event;

	Events();

	virtual ~Events();

	virtual void OnEvent(SDL_Event* Event);

	virtual void OnInputFocus();

	virtual void OnInputBlur();

	virtual void OnKeyDown(SDL_Keycode sym, int mod, int unicode);

	virtual void OnKeyUp(SDL_Keycode sym, int mod, int unicode);

	virtual void OnMouseFocus();

	virtual void OnMouseBlur();

	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);

	virtual void OnMouseWheel(bool Up, bool Down);    //Нет реализации этой шняги

	virtual void OnLButtonDown(int mX, int mY);

	virtual void OnLButtonUp(int mX, int mY);

	virtual void OnRButtonDown(int mX, int mY);

	virtual void OnRButtonUp(int mX, int mY);

	virtual void OnMButtonDown(int mX, int mY);

	virtual void OnMButtonUp(int mX, int mY);

	virtual void OnJoyAxis(int which, int axis, int value);

	virtual void OnJoyButtonDown(int which, int button);

	virtual void OnJoyButtonUp(int which, int button);

	virtual void OnJoyHat(int which, int hat, int value);

	virtual void OnJoyBall(int which, int ball, int xrel, int yrel);

	virtual void OnMinimize();

	virtual void OnRestore();

	virtual void OnResize(int w, int h);

	virtual void OnExpose();

	virtual void OnExit();

	virtual void OnUser(int type, int code, void* data1, void* data2);
};