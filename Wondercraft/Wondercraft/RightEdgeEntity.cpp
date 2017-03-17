#include "RightEdgeEntity.hpp"

#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"

RightEdgeEntity::RightEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

float RightEdgeEntity::getTop() { return position.y - height / 2; }
float RightEdgeEntity::getBottom() { return position.y + height / 2; }

bool RightEdgeEntity::collisionCalc(float& step, float deltaTime, Entity& e) {
	step = 1;

	//only colliding with left edges
	{
		if (velocity.x <= 0)
			return false;

		RightEdgeEntity* rightCast = dynamic_cast<RightEdgeEntity*>(&e);
		if (rightCast != NULL)
			return false;

		TopEdgeEntity* topCast = dynamic_cast<TopEdgeEntity*>(&e);
		if (topCast != NULL)
			return false;

		BottomEdgeEntity* bottomCast = dynamic_cast<BottomEdgeEntity*>(&e);
		if (bottomCast != NULL)
			return false;
	}

	if (!checkMovingAABB(deltaTime, e))
		return false;


	sf::Vector2f v = velocity * deltaTime;

	//potential collision, do more advanced checks

	//relative displacement at the potential time of collision
	float xDisplacement = e.getLeft() - getRight();
	float yDisplacement = v.y / v.x * xDisplacement;

	if (e.getBottom() > getTop() + yDisplacement
			&& e.getTop() < getBottom() + yDisplacement) {
		step = xDisplacement / v.x;
		return true;
	}
	else return false;
}