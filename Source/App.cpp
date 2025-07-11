#include "pch.h"
#include "App.h"
#include "Object.h"

App* App::instance=nullptr;

App::App() {

}
App* App::GetInstance() {
	if (instance == nullptr) {
		instance = new App();
		return instance;
	}
	else
		return instance;
}
void App::Init(const char* title, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	ev = new SDL_Event;
	Object::screen_width = width;
	Object::screen_height = width;
}
void App::Quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void App::Render() {
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
SDL_Renderer* App::GetRenderer() {
	return renderer;
}
SDL_Event* App::GetEvent() {
	return ev;
}
SDL_Window* App::GetWindow() {
	return window;
}