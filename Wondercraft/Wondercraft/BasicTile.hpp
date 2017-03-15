#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"
#include "Tile.hpp"
#include "TileType.hpp"

class BasicTile : public RectangleEntity, public Tile {
public:
	BasicTile(sf::Vector2f position, TileType);
};