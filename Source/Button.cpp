#include "pch.h"
#include "Button.h"

Button::Button(SDL_Renderer* ren, SDL_Event* ev, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color1, SDL_Color color2) 
	: Text(ren, pos, font, text, color1), m_ev(ev) {
	m_normalColor = color1;
	m_highlightColor = color2;
	isMouseOver = false;
}
Button::Button(const Button& obj) : Text(obj.m_ren, Vec2(obj.m_dest.x, obj.m_dest.y), obj.m_font, obj.m_text, obj.m_color), m_ev(obj.m_ev) {
	m_normalColor = obj.m_normalColor;
	m_highlightColor = obj.m_highlightColor;
	isMouseOver = obj.isMouseOver;
}
Button::~Button() {
	//CleanTexture();
}
Button& Button::operator=(const Button& obj) {
	m_ren = obj.m_ren;
	m_ev = obj.m_ev;
	m_dest = obj.m_dest;
	m_font = obj.m_font;
	m_text = obj.m_text;
	m_normalColor = obj.m_normalColor;
	m_highlightColor = obj.m_highlightColor;
	m_sizePercent = obj.m_sizePercent;
	m_origWidth = obj.m_origWidth;
	m_origHeight = obj.m_origHeight;
	m_tex = obj.m_tex;
	isMouseOver = obj.isMouseOver;

	return *this;
}
bool Button::CheckMouseOver() {
	SDL_GetMouseState(&x, &y);
	if(coll::CheckCollisionPoint(*GetDest(), Vec2(x, y)))
		return true;
	return false;
}
bool Button::CheckMouseClick() {
	if (m_ev->type == SDL_MOUSEBUTTONDOWN)
		if (m_ev->button.button == SDL_BUTTON_LEFT && CheckMouseOver())
			return true;
	return false;
}
bool Button::CheckMouseClickOutside() {
	if (m_ev->type == SDL_MOUSEBUTTONDOWN)
		if (m_ev->button.button == SDL_BUTTON_LEFT && !CheckMouseOver())
			return true;
	return false;
}
void Button::Update() {
	if (CheckMouseOver() && !isMouseOver) {
		isMouseOver = true;
		ChangeColor(m_highlightColor);
	}
	else if (!CheckMouseOver() && isMouseOver) {
		isMouseOver = false;
		ChangeColor(m_normalColor);
	}
}
void Button::Render() {
	Text::Render();
}