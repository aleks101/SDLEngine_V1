#include "pch.h"
#include "Camera.h"

Camera::Camera() {
	cameraPos = NULL;
	prevXoffset = 0;
	prevYoffset = 0;
}
void Camera::Init(const SDL_Rect* _cameraPos) {
	cameraPos = _cameraPos;
	if(cameraPos!=NULL)
		prevCamera = *cameraPos;
}
void Camera::SetCamera() {
	if (cameraPos != NULL) {
		prevXoffset = cameraPos->x - prevCamera.x;
		prevYoffset = cameraPos->y - prevCamera.y;

		prevCamera = *cameraPos;
	}
}
bool Camera::CheckForChange() {
	if (prevXoffset != 0 || prevYoffset != 0) {
		return true;
	}
	return false;
}
Vec2 Camera::CalculateChange() {
	if (cameraPos != nullptr) {
		//if player's position gets below x0 and y0, camera stops working properly
		change.x = -prevXoffset;
		change.y = -prevYoffset;

		return change;
	}
	return Vec2(0, 0);
}