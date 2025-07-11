#include "pch.h"
#include "Text.h"

Text::Text(SDL_Renderer* ren, Vec2 pos, TTF_Font* _font, std::string _text, SDL_Color _color) : Object({0,0,0,0}) {
	m_ren = ren;
	m_dest.x = pos.x;
	m_dest.y = pos.y;
	m_text = _text;
	m_color = _color;
	m_font = _font;
	m_permaText = "";

	CreateText();
	m_origWidth = m_dest.w;
	m_origHeight = m_dest.h;
	m_sizePercent = 100;
	SetDest(m_dest);
}
Text::Text(const Text& obj) : Object(obj.m_dest), m_text(obj.m_text), m_permaText(obj.m_permaText), m_color(obj.m_color), m_font(obj.m_font), 
	m_origWidth(obj.m_origWidth), m_origHeight(obj.m_origHeight), m_sizePercent(obj.m_sizePercent) {
	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
}
Text::~Text() {
}
Text& Text::operator=(const Text& obj) {
	m_text = obj.m_text;
	m_permaText = obj.m_permaText;
	m_color = obj.m_color;
	m_font = obj.m_font;
	m_sizePercent = obj.m_sizePercent;
	m_origWidth = obj.m_origWidth;
	m_origHeight = obj.m_origHeight;

	m_ren = obj.m_ren;
	m_dest = obj.m_dest;
	m_tex = obj.m_tex;

	return *this;
}
void Text::Render() {
	if (m_ren != nullptr && m_tex != nullptr)
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_dest);
}
void Text::Update() {

}
SDL_Rect* Text::GetDest() {
	return &m_dest;
}
SDL_Rect* Text::GetSrc() {
	return &m_src;
}
SDL_Rect* Text::GetScreen() {
	return &m_screen;
}
void Text::CreateText() {
	SDL_Surface* surf = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
	if (!surf) {
	LOG("Failed to render text: ");
	LOG(TTF_GetError());
	LOG("\n");
	}
	if (!m_ren)
		LOG("renderer error");

	m_tex = SDL_CreateTextureFromSurface(m_ren, surf);
	if (!m_tex)
		LOG("tex error");
	SDL_QueryTexture(m_tex, NULL, NULL, &m_dest.w, &m_dest.h);
	SetDest(m_dest);
	SDL_FreeSurface(surf);
}
void Text::ChangeText(std::string _text) {
	if (m_text != (m_permaText + _text)) {
		m_text = m_permaText + _text;
		SDL_DestroyTexture(m_tex);

		CreateText();

		m_origWidth = m_dest.w;
		m_origHeight = m_dest.h;
		m_sizePercent = 100;
	}
}
void Text::ChangeText(int num) {
	std::string numString = std::to_string(num);
	if (m_text != (m_permaText + numString)) {
		m_text = m_permaText + numString;
		SDL_DestroyTexture(m_tex);

		CreateText();

		m_origWidth = m_dest.w;
		m_origHeight = m_dest.h;
		m_sizePercent = 100;
	}
}
void Text::SetNoChangeText(int indexTo) {

}
void Text::SetNoChangeText(std::string newText) {
	m_permaText = newText;
}
void Text::ChangeColor(SDL_Color color) {
	m_color = color;
	SDL_SetTextureColorMod(m_tex, m_color.r, m_color.g, m_color.b);
}
void Text::ChangeSize(int num) {
	//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

	int prevSize = m_sizePercent;
	m_sizePercent = num;

	SDL_Rect dest = *GetDest();

	dest.w = (m_sizePercent * m_dest.w) / prevSize;
	dest.h = (m_sizePercent * m_dest.h) / prevSize;

	SetDest(dest);
}
void Text::ChangeSizeFor(int num) {
	//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

	int prevSize = m_sizePercent;
	m_sizePercent += num;

	SDL_Rect dest = *GetDest();

	dest.w = (m_sizePercent * m_dest.w) / prevSize;
	dest.h = (m_sizePercent * m_dest.h) / prevSize;

	SetDest(dest);
}
void Text::CleanTexture() {
	SDL_DestroyTexture(m_tex);
	m_tex = nullptr;
}