#include "BasicTile.hpp"

BasicTile::BasicTile(TileType::TileType t, sf::Vector2f position)
		: RectangleEntity(position, sf::Vector2f(1, 1)), Tile(t) {}