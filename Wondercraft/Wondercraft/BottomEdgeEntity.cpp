#include "BottomEdgeEntity.hpp"

BottomEdgeEntity::BottomEdgeEntity(sf::Vector2f& position, float width)
	: Entity(position) {}

sf::Vector2f BottomEdgeEntity::getSize() { return sf::Vector2f(width, 0); }
float BottomEdgeEntity::getLeft() { return position.x - width / 2; }
float BottomEdgeEntity::getRight() { return position.x + width / 2; }

float BottomEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	return -1;
}