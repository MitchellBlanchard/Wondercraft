#include "ThinPlatform.hpp"

ThinPlatform::ThinPlatform(sf::Vector2f position, TileType t)
	: TopEdgeEntity(position, 1), Tile(t) {}

float ThinPlatform::getTop() { return position.y - 0.5; }
float ThinPlatform::getBottom() { return position.y - 0.5; }