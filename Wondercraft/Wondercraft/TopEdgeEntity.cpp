#include "TopEdgeEntity.hpp"

TopEdgeEntity::TopEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position), width(width) {}

sf::Vector2f TopEdgeEntity::getSize() { return sf::Vector2f(width, 0); }
float TopEdgeEntity::getLeft() { return position.x - width / 2; }
float TopEdgeEntity::getRight() { return position.x + width / 2; }

float TopEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	return -1;
}