#pragma once

#include "Object.h"

class Slider : public Object
{
public:
	Slider();
	Slider(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect dest, int slots, SDL_Color color);

	void Update();
	void Render();

	SDL_Rect* GetDest() {
		return &m_dest;
	}
	SDL_Rect* GetScreen() {
		return &m_screen;
	}
	SDL_Rect* GetSrc() {
		return &m_src;
	}
private:
	int m_slotWidth=0;
	int m_slots;
	bool m_isClicked = false;

	SDL_Event* m_ev = nullptr;
	SDL_Color m_color = {255,255,255,255};
	int m_mousePosX = 0, m_mousePosY = 0;
};

