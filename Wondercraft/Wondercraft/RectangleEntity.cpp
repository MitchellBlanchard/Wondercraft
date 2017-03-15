#include "RectangleEntity.hpp"

RectangleEntity::RectangleEntity(sf::Vector2f& position, sf::Vector2f& size)
		: Entity(position),
		leftEdge  (position + sf::Vector2f(-size.x / 2, 0), size.y),
		rightEdge (position + sf::Vector2f( size.x / 2, 0), size.y),
		topEdge   (position + sf::Vector2f(0, -size.y / 2), size.x),
		bottomEdge(position + sf::Vector2f(0,  size.y / 2), size.x) {}

float RectangleEntity::getLeft() { return leftEdge.getLeft(); }
float RectangleEntity::getRight() { return rightEdge.getRight(); }
float RectangleEntity::getTop() { return topEdge.getTop(); }
float RectangleEntity::getBottom() { return bottomEdge.getBottom(); }

void RectangleEntity::setVelocity(sf::Vector2f& v) {
	Entity::setVelocity(v);
	leftEdge.setVelocity(v);
	rightEdge.setVelocity(v);
	topEdge.setVelocity(v);
	bottomEdge.setVelocity(v);
}

float RectangleEntity::collisionCalc(float deltaTime, Entity& e) {
	if (!checkMovingAABB(deltaTime, e))
		return -1;

	//potential collision, do more advanced checks

	float horizontalCollisionStep = -1;
	if (velocity.x < 0) {
		horizontalCollisionStep = leftEdge.collisionCalc(deltaTime, e);
	}
	else if (velocity.x > 0) {
		horizontalCollisionStep = rightEdge.collisionCalc(deltaTime, e);
	}

	float verticalCollisionStep = -1;
	if (velocity.y < 0) {
		verticalCollisionStep = topEdge.collisionCalc(deltaTime, e);
	}
	else if (velocity.y > 0) {
		verticalCollisionStep = bottomEdge.collisionCalc(deltaTime, e);
	}

	if (horizontalCollisionStep < 0)
		return verticalCollisionStep;

	else if (verticalCollisionStep < 0)
		return horizontalCollisionStep;

	else if (horizontalCollisionStep < verticalCollisionStep)
		return horizontalCollisionStep;

	else return verticalCollisionStep;
}