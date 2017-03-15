#include "Entity.hpp"

//Entity
Entity::Entity(sf::Vector2f& position)
		: position(position) {}

sf::Vector2f Entity::getSize() { return sf::Vector2f(0, 0); }
float Entity::getLeft() { return position.x; }
float Entity::getRight() { return position.x; }
float Entity::getTop() { return position.y; }
float Entity::getBottom() { return position.y; }

bool Entity::checkAABB(Entity& e) {
	//check if e is too far left
	if (e.getRight() < getLeft())
		return false;

	//check if e is too far right
	if (e.getLeft() > getRight())
		return false;

	//check if e is too high
	if (e.getBottom() < getTop())
		return false;

	//check if e is too low
	if (e.getTop() > getBottom())
		return false;

	return true;
}

bool Entity::checkMovingAABB(float deltaTime, Entity& e) {
	sf::Vector2f v = velocity * deltaTime;

	//check if e is too far left
	float leftBound = getLeft();
	if (v.x < 0) leftBound += v.x;

	if (e.getRight() < leftBound)
		return false;

	//check if e is too far right
	float rightBound = getRight();
	if (v.x > 0) rightBound += v.x;

	if (e.getLeft() > rightBound)
		return false;

	//check if e is too high
	float topBound = getTop();
	if (v.y < 0) topBound += v.y;

	if (e.getBottom() < topBound)
		return false;

	//check if e is too low
	float bottomBound = getBottom();
	if (v.y > 0) bottomBound += v.y;

	if (e.getTop() > bottomBound)
		return false;

	return true;
}