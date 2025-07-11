#include "pch.h"
#include "FPS.h"
#include "TimeD.h"

int FPS::fps = 0;

void FPS::CalcFPS() {
	fps = 1 / (int)TimeD::DeltaTime();
}
int FPS::GetFPS() {
	return fps;
}