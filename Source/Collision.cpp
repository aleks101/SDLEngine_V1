#include "pch.h"
#include "Collision.h"

namespace coll {
	bool CheckCollisionAABB(const SDL_Rect A, const SDL_Rect B) {
		int leftA = A.x;
		int rightA = A.x + A.w;
		int topA = A.y;
		int bottomA = A.y + A.h;

		int leftB = B.x;
		int rightB = B.x + B.w;
		int topB = B.y;
		int bottomB = B.y + B.h;

        if (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB) {
            return true;
        }
        return false;
	}
    bool CheckCollisionX(const SDL_Rect A, const SDL_Rect B) {
        int leftA = A.x;
        int rightA = A.x + A.w;
        int topA = A.y;
        int bottomA = A.y + A.h;

        int leftB = B.x;
        int rightB = B.x + B.w;
        int topB = B.y;
        int bottomB = B.y + B.h;

        if (rightA > leftB && leftA < leftB) {
            return true;
        }
        else if (leftA < rightB && rightA > rightB) {
            return true;
        }
        return false;
    }
    bool CheckCollisionY(const SDL_Rect A, const SDL_Rect B) {
        int leftA = A.x;
        int rightA = A.x + A.w;
        int topA = A.y;
        int bottomA = A.y + A.h;

        int leftB = B.x;
        int rightB = B.x + B.w;
        int topB = B.y;
        int bottomB = B.y + B.h;

        if (topA >= topB && topA <= bottomB) {
            return true;
        }
        else if (bottomA >= topB && bottomA < bottomB) {
            return true;
        }
        return false;
                 
    }
    bool CheckCollisionPoint(const SDL_Rect A, const Vec2 B) {
        int leftA = A.x;
        int rightA = A.x + A.w;
        int topA = A.y;
        int bottomA = A.y + A.h;

        if (B.x >= leftA && B.x <= rightA && B.y >= topA && B.y <= bottomA) {
            return true;
        }
        return false;
    }
}