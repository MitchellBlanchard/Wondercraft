#include "LeftEdgeEntity.hpp"

#include "TopEdgeEntity.hpp"
#include "BottomEdgeEntity.hpp"

LeftEdgeEntity::LeftEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

float LeftEdgeEntity::getTop() { return position.y - height / 2; }
float LeftEdgeEntity::getBottom() { return position.y + height / 2; }

bool LeftEdgeEntity::collisionCalc(float& step, float deltaTime, Entity& e) {
	step = 1;

	//only colliding with right edges
	{
		if (velocity.x >= 0)
			return false;

		LeftEdgeEntity* leftCast = dynamic_cast<LeftEdgeEntity*>(&e);
		if (leftCast != NULL)
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
	float xDisplacement = e.getRight() - getLeft();
	float yDisplacement = v.y / v.x * xDisplacement;

	if (e.getBottom() > getTop() + yDisplacement
			&& e.getTop() < getBottom() + yDisplacement) {
		step = xDisplacement / v.x;
		return true;
	}
	else return false;
}