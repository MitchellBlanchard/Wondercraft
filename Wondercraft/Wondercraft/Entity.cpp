#include "Entity.hpp"

//Entity
Entity::Entity(sf::Vector2f& position)
		: position(position) {}

float Entity::getLeft() { return position.x; }
float Entity::getRight() { return position.x; }
float Entity::getTop() { return position.y; }
float Entity::getBottom() { return position.y; }
sf::Vector2f Entity::getSize() {
	return sf::Vector2f(getRight() - getLeft(), getBottom() - getTop());
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}

void Entity::setVelocity(sf::Vector2f& v) {
	velocity = v;
}

sf::Vector2f Entity::getPosition() {
	return position;
}

void Entity::setPosition(sf::Vector2f& p) {
	position = p;
}



bool Entity::checkAABB(Entity& e) {
	float threshold = 0.0001;

	//check if e is too far left
	if (e.getRight() < getLeft() + threshold)
		return false;

	//check if e is too far right
	if (e.getLeft() > getRight() - threshold)
		return false;

	//check if e is too high
	if (e.getBottom() < getTop() + threshold)
		return false;

	//check if e is too low
	if (e.getTop() > getBottom() - threshold)
		return false;

	return true;
}

bool Entity::checkMovingAABB(float deltaTime, Entity& e) {
	float threshold = 0.0001;

	sf::Vector2f v = velocity * deltaTime;

	//check if e is too far left
	float leftBound = getLeft();
	if (v.x < 0) leftBound += v.x;

	if (e.getRight() < leftBound + threshold)
		return false;

	//check if e is too far right
	float rightBound = getRight();
	if (v.x > 0) rightBound += v.x;

	if (e.getLeft() > rightBound - threshold)
		return false;

	//check if e is too high
	float topBound = getTop();
	if (v.y < 0) topBound += v.y;

	if (e.getBottom() < topBound + threshold)
		return false;

	//check if e is too low
	float bottomBound = getBottom();
	if (v.y > 0) bottomBound += v.y;

	if (e.getTop() > bottomBound - threshold)
		return false;

	return true;
}