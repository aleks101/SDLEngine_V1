#include "pch.h"
#include "Tile.h"

int Tile::streampos = 0;

Tile::Tile(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, bool isSolid) : 
	Object(dest) {
	CenterObj(player);
	m_ren = ren;
	m_tex = tex;
	m_screen = dest;
	m_src = dest;
	SetSolid(isSolid);
}
Tile::Tile(const Tile& obj) : Object(obj.m_dest) {
	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
	m_screen = obj.m_dest;
	m_src = obj.m_dest;
	SetSolid(obj.m_isSolid);
}
Tile::~Tile() {

}
Tile& Tile::operator=(const Tile& obj) {
	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
	m_dest = obj.m_dest;
	m_screen = obj.m_screen;
	m_src = obj.m_src;
	SetSolid(obj.m_isSolid);
	return *this;
}
void Tile::Render() {
	if (!CheckIfObjectOutOfScreen())
		if (m_ren != nullptr && m_tex != nullptr)
			SDL_RenderCopy(m_ren, m_tex, &m_src, &m_screen);
}
void Tile::Update() {

}