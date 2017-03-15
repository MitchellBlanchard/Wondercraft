#include "Entity.hpp"

Entity::Entity(sf::Vector2f& spawn) {
	position = spawn;
}

float Entity::collisionCalc(float dt, Entity& e) {
	//check if e is too far left
	float leftBound = getLeft();
	if (velocity.x < 0) leftBound += velocity.x;

	if (e.getRight() < leftBound)
		return -1;

	//check if e is too far right
	float rightBound = getRight();
	if (velocity.x > 0) rightBound += velocity.x;

	if (e.getLeft() > rightBound)
		return -1;

	//check if e is too high
	float topBound = getTop();
	if (velocity.y < 0) topBound += velocity.y;

	if (e.getBottom() < topBound)
		return -1;

	//check if e is too low
	float bottomBound = getBottom();
	if (velocity.y > 0) bottomBound += velocity.y;

	if (e.getTop() > bottomBound)
		return -1;


	//potential collision, do more advanced checks depending on velocity direction

	if (velocity.x < 0) {

	}
	else if (velocity.x > 0) {

	}
	else {

	}
}

float Entity::getLeft() { return position.x - size.x; }
float Entity::getRight() { return position.x + size.x; }
float Entity::getTop() { return position.y - size.y; }
float Entity::getBottom() { return position.y + size.y; }