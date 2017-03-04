#include "Entity.hpp"

Entity::Entity(sf::Vector2f pos, sf::Vector2f dim) {
	left = pos.x - dim.x / 2;
	right = pos.x + dim.x / 2;

	top = pos.y - dim.y / 2;
	bottom = pos.y + dim.y / 2;
}