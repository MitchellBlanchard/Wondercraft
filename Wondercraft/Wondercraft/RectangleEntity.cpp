#include "RectangleEntity.hpp"

RectangleEntity::RectangleEntity(sf::Vector2f& position, sf::Vector2f& size)
	: Entity(position) {

}

sf::Vector2f RectangleEntity::getSize() { return sf::Vector2f(); }
float RectangleEntity::getTop() { return 0; }
float RectangleEntity::getBottom() { return 0; }
float RectangleEntity::getLeft() { return 0; }
float RectangleEntity::getRight() { return 0; }

float RectangleEntity::collisionCalc(float dt, Entity& e) {
	if (!checkMovingAABB(dt, e))
		return -1;

	//potential collision, do more advanced checks depending on velocity direction

	if (velocity.x < 0) {
		if (velocity.y < 0) {

		}
		else if (velocity.y > 0) {

		}
		else {

		}
	}
	else if (velocity.x > 0) {

	}
	else {

	}
}