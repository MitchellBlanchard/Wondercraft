#include "RightEdgeEntity.hpp"

RightEdgeEntity::RightEdgeEntity(sf::Vector2f& position, float height)
	: Entity(position), height(height) {}

sf::Vector2f RightEdgeEntity::getSize() { return sf::Vector2f(0, height); }
float RightEdgeEntity::getTop() { return position.y - height / 2; }
float RightEdgeEntity::getBottom() { return position.y + height / 2; }

float RightEdgeEntity::collisionCalc(float deltaTime, Entity& e) {
	return -1;
}