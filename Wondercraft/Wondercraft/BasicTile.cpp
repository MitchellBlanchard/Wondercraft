#include "BasicTile.hpp"

BasicTile::BasicTile(sf::Vector2f position, TileType t)
		: RectangleEntity(position, sf::Vector2f(1, 1)), Tile(t) {}