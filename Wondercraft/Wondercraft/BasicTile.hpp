#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"
#include "Tile.hpp"
#include "TileType.hpp"

// Basic tiles do not have any special collision properties.
// They store a TileType, and thus support any tile texture.
class BasicTile : public RectangleEntity, public Tile {
public:
	BasicTile(TileType::TileType, sf::Vector2f position = sf::Vector2f());
};