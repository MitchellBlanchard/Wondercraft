#include "BottomEdgeEntity.hpp"

BottomEdgeEntity::BottomEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position), width(width) {}

float BottomEdgeEntity::getLeft() { return position.x - width / 2; }
float BottomEdgeEntity::getRight() { return position.x + width / 2; }

float BottomEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	//only colliding with top edges
	if (velocity.y <= 0)
		return -1;

	if (!checkMovingAABB(deltaTime, e))
		return -1;


	sf::Vector2f v = velocity * deltaTime;

	//potential collision, do more advanced checks

	//relative displacement at the potential time of collision
	float yDisplacement = e.getTop() - getBottom();
	float xDisplacement = v.x / v.y * yDisplacement;

	if (e.getRight() > getLeft() + xDisplacement
		&& e.getLeft() < getRight() + xDisplacement) {
		return yDisplacement / v.y;
	}
	else return -1;
}