#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleEntity.hpp"
#include "Tile.hpp"
#include "TileType.hpp"

class BasicTile : public RectangleEntity, public Tile {
public:
	BasicTile(TileType, sf::Vector2f position = sf::Vector2f());
};