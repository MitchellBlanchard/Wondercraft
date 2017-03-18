#pragma once

#include "TileType.hpp"

class Tile {
public:
	Tile(TileType::TileType);

	TileType::TileType type;
};