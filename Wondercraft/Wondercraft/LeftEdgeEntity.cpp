#include "LeftEdgeEntity.hpp"

LeftEdgeEntity::LeftEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

sf::Vector2f LeftEdgeEntity::getSize() { return sf::Vector2f(0, height); }
float LeftEdgeEntity::getTop() { return position.y - height / 2; }
float LeftEdgeEntity::getBottom() { return position.y + height / 2; }

float LeftEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	//only colliding with right edges
	if (velocity.x >= 0)
		return -1;

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