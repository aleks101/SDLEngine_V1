#include "pch.h"
#include "Slider.h"

#include "Collision.h"

Slider::Slider(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect dest, int slots, SDL_Color color)
	: Object(dest), m_slots(slots), m_color(color) {
	m_ren = ren;
	m_ev = ev;
	m_slotWidth = m_dest.w / slots;
}
Slider::Slider() : Object() {

}
void Slider::Render() {

}
void Slider::Update() {
	SDL_GetMouseState(&m_mousePosX, &m_mousePosY);
	if (m_ev != nullptr && m_ev->type == SDL_MOUSEBUTTONDOWN && m_ev->button.button == SDL_BUTTON_LEFT) {
		if (coll::CheckCollisionPoint(m_dest, Vec2(m_mousePosX, m_mousePosY)))
			m_isClicked = true;
		else
			m_isClicked = false;
	}
	else if (m_ev != nullptr && m_ev->type == SDL_MOUSEBUTTONUP && m_ev->button.button == SDL_BUTTON_LEFT)
		m_isClicked = false;

	if (m_isClicked) {

	}
}