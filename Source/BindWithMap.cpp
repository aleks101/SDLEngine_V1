#include "pch.h"
#include "BindWithMap.h"

BindWithMap::BindWithMap(Map* map) : m_map(map) {}
BindWithMap::BindWithMap() : m_map(NULL) {}
BindWithMap::~BindWithMap() {

}

void BindWithMap::SetMap(Map* map) {
	m_map = map;
}
bool BindWithMap::CheckCollisionDestWithMap(Object* object) {
	if (m_map != NULL && object != NULL)
		if (m_map->CheckCollisionDest(object))
			return true;
	return false;
}
bool BindWithMap::CheckCollisionScreenWithMap(Object* object) {
	if (m_map != NULL && object != NULL)
		if (m_map->CheckCollisionScreen(object))
			return true;
	return false;
}
bool BindWithMap::CheckCollisionDirectionWithMap(Object* object, bool destOrScreen, bool XorY) {
	if (m_map != NULL && object != NULL) {
		if (m_map->CheckCollision(object, destOrScreen, XorY))
			return true;
	}
	return false;
}