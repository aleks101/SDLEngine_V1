#include "pch.h"
#include "Physics.h"

namespace physics {
	Vec2 CalculateVelocity(Vec2 currentPos, Vec2 targetPos, const float magnitude) {
		if (currentPos != targetPos) {
			Vec2 D = targetPos - currentPos;
			int X = pow(targetPos.x - currentPos.x, 2);
			int Y = pow(targetPos.y - currentPos.y, 2);
			Vec2 velocity = D * (magnitude / static_cast<float>(std::sqrt(X + Y)));
			return velocity;
		}
		return Vec2(0, 0);
	}
}