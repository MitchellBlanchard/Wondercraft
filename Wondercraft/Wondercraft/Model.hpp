#pragma once

#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"

#include "TileTypes.hpp"

class Model : public UpdateableGroup {
public:
	Model();

	void readTerrain(std::string);
	
	int level_Height, level_Width;

	Tile_Type** mapTiles;

private:
	std::map<sf::Color, Tile_Type> tile_Conversion;
	void init_Tyle_Type_Map();
	
};