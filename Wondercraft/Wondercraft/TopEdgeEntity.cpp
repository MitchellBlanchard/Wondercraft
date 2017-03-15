#include "TopEdgeEntity.hpp"

TopEdgeEntity::TopEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position), width(width) {}

float TopEdgeEntity::getLeft() { return position.x - width / 2; }
float TopEdgeEntity::getRight() { return position.x + width / 2; }

float TopEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	//only colliding with bottom edges
	if (velocity.y >= 0)
		return -1;

	if (!checkMovingAABB(deltaTime, e))
		return -1;


	sf::Vector2f v = velocity * deltaTime;

	//potential collision, do more advanced checks

	//relative displacement at the potential time of collision
	float yDisplacement = e.getBottom() - getTop();
	float xDisplacement = v.x / v.y * yDisplacement;

	if (e.getRight() > getLeft() + xDisplacement
		&& e.getLeft() < getRight() + xDisplacement) {
		return yDisplacement / v.y;
	}
	else return -1;
}