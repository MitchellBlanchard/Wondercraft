#include "BottomEdgeEntity.hpp"

#include "LeftEdgeEntity.hpp"
#include "RightEdgeEntity.hpp"

BottomEdgeEntity::BottomEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position), width(width) {}

float BottomEdgeEntity::getLeft() { return position.x - width / 2; }
float BottomEdgeEntity::getRight() { return position.x + width / 2; }

bool BottomEdgeEntity::collisionCalc(float& step, float deltaTime, Entity& e) {
	step = 1;

	//only colliding with top edges
	{
		if (velocity.y <= 0)
			return false;

		LeftEdgeEntity* leftCast = dynamic_cast<LeftEdgeEntity*>(&e);
		if (leftCast != NULL)
			return false;

		RightEdgeEntity* rightCast = dynamic_cast<RightEdgeEntity*>(&e);
		if (rightCast != NULL)
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
	float yDisplacement = e.getTop() - getBottom();
	float xDisplacement = v.x / v.y * yDisplacement;

	if (e.getRight() > getLeft() + xDisplacement
			&& e.getLeft() < getRight() + xDisplacement) {
		step = yDisplacement / v.y;
		return true;
	}
	else return false;
}