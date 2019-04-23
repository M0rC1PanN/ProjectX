#include "pch.h"

#include "Camera.h"

Camera Camera::CameraControl;

Camera::Camera() {
	X = MAP_WBLOCK / 2;
	Y = MAP_HBLOCK / 2;

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}

void Camera::OnMove(float MoveX, float MoveY) {
	X += MoveX;
	Y += MoveY;
}

float Camera::GetX() {
	if (TargetX != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetX - (WWIDTH / 2);
		}

		return *TargetX;
	}

	return X;
}

float Camera::GetY() {
	if (TargetY != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetY - (WHEIGHT / 2);
		}

		return *TargetY;
	}

	return Y;
}

void Camera::SetPos(float X, float Y) {
	this->X = X;
	this->Y = Y;
}

void Camera::SetTarget(float* X, float* Y) {
	TargetX = X;
	TargetY = Y;
}