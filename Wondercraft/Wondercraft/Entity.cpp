#include "Entity.hpp"

RectangleEntity::RectangleEntity(sf::Vector2f pos, sf::Vector2f dim) {
	rx = dim.x / 2;
	ry = dim.y / 2;
	setPosition(pos.x - rx, pos.y - ry);
}