#include "TopEdgeEntity.hpp"

#include "LeftEdgeEntity.hpp"
#include "RightEdgeEntity.hpp"

TopEdgeEntity::TopEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position), width(width) {}

float TopEdgeEntity::getLeft() { return position.x - width / 2; }
float TopEdgeEntity::getRight() { return position.x + width / 2; }

bool TopEdgeEntity::collisionCalc(float& step, float deltaTime, Entity& e) {
	step = 1;

	//only colliding with bottom edges
	{
		if (velocity.y >= 0)
			return false;

		LeftEdgeEntity* leftCast = dynamic_cast<LeftEdgeEntity*>(&e);
		if (leftCast != NULL)
			return false;

		RightEdgeEntity* rightCast = dynamic_cast<RightEdgeEntity*>(&e);
		if (rightCast != NULL)
			return false;

		TopEdgeEntity* topCast = dynamic_cast<TopEdgeEntity*>(&e);
		if (topCast != NULL)
			return false;
	}

	if (!checkMovingAABB(deltaTime, e))
		return false;


	sf::Vector2f v = velocity * deltaTime;

	//potential collision, do more advanced checks

	//relative displacement at the potential time of collision
	float yDisplacement = e.getBottom() - getTop();
	float xDisplacement = v.x / v.y * yDisplacement;

	if (e.getRight() > getLeft() + xDisplacement
			&& e.getLeft() < getRight() + xDisplacement) {
		step = yDisplacement / v.y;
		return true;
	}
	else return false;
}