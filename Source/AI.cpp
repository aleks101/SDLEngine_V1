#include "pch.h"
#include "AI.h"

AI::AI(SDL_Rect* playerDest, SDL_Rect* dest) : m_enemyDest(playerDest), m_entityDest(dest) {
	LOG("AI CONSTRUCTED\n");
}
Vec2 AI::Follow(float speed, Vec2 destination) {
	return physics::CalculateVelocity(Vec2(m_entityDest->x, m_entityDest->y), Vec2(m_enemyDest->x, m_enemyDest->y), speed);
}