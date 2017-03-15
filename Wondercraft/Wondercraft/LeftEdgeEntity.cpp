#include "LeftEdgeEntity.hpp"

#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"

LeftEdgeEntity::LeftEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

float LeftEdgeEntity::getTop() { return position.y - height / 2; }
float LeftEdgeEntity::getBottom() { return position.y + height / 2; }

float LeftEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	//only colliding with right edges
	{
		if (velocity.x >= 0)
			return -1;

		LeftEdgeEntity* leftCast = dynamic_cast<LeftEdgeEntity*>(&e);
		if (leftCast != NULL)
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
	float xDisplacement = e.getRight() - getLeft();
	float yDisplacement = v.y / v.x * xDisplacement;

	if (e.getBottom() > getTop() + yDisplacement
			&& e.getTop() < getBottom() + yDisplacement) {
		return xDisplacement / v.x;
	}
	else return -1;
}