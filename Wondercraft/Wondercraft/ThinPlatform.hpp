#pragma once

#include <SFML/Graphics.hpp>

#include "TopEdgeEntity.hpp"
#include "Tile.hpp"
#include "TileType.hpp"

class ThinPlatform : public TopEdgeEntity, public Tile {
public:
	ThinPlatform(TileType, sf::Vector2f position = sf::Vector2f());

	//override getTop() and getBottom() to essentially shift the edge up by half a tile
	//from the position coordinates (to the top of the tile)
	float getTop();
	float getBottom();
};