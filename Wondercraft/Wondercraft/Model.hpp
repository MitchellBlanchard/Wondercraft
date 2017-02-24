#pragma once

#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"

#include "TileTypes.hpp"

class Model : public UpdateableGroup {
public:
	Model();

	/*
		Initializes the level's 2D tile array (mapTiles) from a given image file.
	*/
	void readMapTiles(std::string filepath);

private:
	std::map<sf::Color, Tile_Type> tileConversion;

	/*
		Maps sf::Color objects to Tile_Type enums. (Stored in the tileConversion member.)
		These hardcoded colors will represent different types of tiles
		when read from an image file.
	*/
	void initTyleTypeMap();

	int levelHeight, levelWidth;
	Tile_Type** mapTiles;
	
};