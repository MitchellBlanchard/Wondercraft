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

void RectangleEntity::setPosition(sf::Vector2f& p) {
	sf::Vector2f movement = p - position;

	Entity::setPosition(p);

	leftEdge.setPosition(leftEdge.getPosition() + movement);
	rightEdge.setPosition(rightEdge.getPosition() + movement);
	topEdge.setPosition(topEdge.getPosition() + movement);
	bottomEdge.setPosition(bottomEdge.getPosition() + movement);
}

void RectangleEntity::setSize(sf::Vector2f newSize) {
	leftEdge =     LeftEdgeEntity(position + sf::Vector2f(-newSize.x / 2, 0), newSize.y);
	rightEdge =   RightEdgeEntity(position + sf::Vector2f( newSize.x / 2, 0), newSize.y);
	topEdge =       TopEdgeEntity(position + sf::Vector2f(0, -newSize.y / 2), newSize.x);
	bottomEdge = BottomEdgeEntity(position + sf::Vector2f(0,  newSize.y / 2), newSize.x);
}

bool RectangleEntity::collisionCalc(float& step, float deltaTime, Entity& e) {
	if (!checkMovingAABB(deltaTime, e))
		return false;

	//potential collision, do more advanced checks

	//collision with left or right edge
	bool horizontalCollision = false;
	float horizontalStep = 1;
	if (velocity.x < 0) {
		horizontalCollision = leftEdge.collisionCalc(horizontalStep, deltaTime, e);
	}
	else if (velocity.x > 0) {
		horizontalCollision = rightEdge.collisionCalc(horizontalStep, deltaTime, e);
	}

	//collision with top or bottom edge
	bool verticalCollision = false;
	float verticalStep = 1;
	if (velocity.y < 0) {
		verticalCollision = topEdge.collisionCalc(verticalStep, deltaTime, e);
	}
	else if (velocity.y > 0) {
		verticalCollision = bottomEdge.collisionCalc(verticalStep, deltaTime, e);
	}

	//if no horizontal collision, take the vertical one
	if (!horizontalCollision) {
		step = verticalStep;
		return verticalCollision;
	}

	//if no vertical collision, take the horizontal one
	else if (!verticalCollision) {
		step = horizontalStep;
		return horizontalCollision;
	}

	//collides either way, take the closest one

	else if (horizontalCollision < verticalCollision) {
		step = horizontalStep;
		return horizontalCollision;
	} else {
		step = verticalStep;
		return verticalCollision;
	}
}