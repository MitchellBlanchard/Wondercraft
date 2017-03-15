#include "RightEdgeEntity.hpp"

#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"

RightEdgeEntity::RightEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

float RightEdgeEntity::getTop() { return position.y - height / 2; }
float RightEdgeEntity::getBottom() { return position.y + height / 2; }

float RightEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	//only colliding with left edges
	{
		if (velocity.x <= 0)
			return -1;

		RightEdgeEntity* rightCast = dynamic_cast<RightEdgeEntity*>(&e);
		if (rightCast != NULL)
			return -1;

		TopEdgeEntity* topCast = dynamic_cast<TopEdgeEntity*>(&e);
		if (topCast != NULL)
			return -1;

		BottomEdgeEntity* bottomCast = dynamic_cast<BottomEdgeEntity*>(&e);
		if (bottomCast != NULL)
			return -1;
	}

	if (!checkMovingAABB(deltaTime, e))
		return -1;


	sf::Vector2f v = velocity * deltaTime;

	//potential collision, do more advanced checks

	//relative displacement at the potential time of collision
	float xDisplacement = e.getLeft() - getRight();
	float yDisplacement = v.y / v.x * xDisplacement;

	if (e.getBottom() > getTop() + yDisplacement
			&& e.getTop() < getBottom() + yDisplacement) {
		return xDisplacement / v.x;
	}
	else return -1;
}