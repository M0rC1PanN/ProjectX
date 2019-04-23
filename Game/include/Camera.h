//Этот класс помогает нам двигать камеру происходящего на карте, эту камеру мы закрепили за главным персонажем

#pragma once

#include <SDL.h>

#include "Define.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class Camera {
public:
	static Camera CameraControl;

private:
	float X;
	float Y;

	float* TargetX;
	float* TargetY;

public:
	float TargetMode;

public:
	Camera();

public:
	void OnMove(float MoveX, float MoveY);

public:
	float GetX();
	float GetY();

public:
	void SetPos(float X, float Y);

	void SetTarget(float* X, float* Y);
};
