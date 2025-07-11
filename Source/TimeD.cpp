#include "pch.h"
#include "TimeD.h"
#include <SDL.h>

float TimeD::s_prevTime = 0;
float TimeD::deltaTime = 0;

void TimeD::CalcDeltaTime() {
	float currTime = SDL_GetTicks();
	deltaTime = (currTime - s_prevTime) / 1000;
	s_prevTime = currTime;
}
float TimeD::DeltaTime() {
	return deltaTime;
} 