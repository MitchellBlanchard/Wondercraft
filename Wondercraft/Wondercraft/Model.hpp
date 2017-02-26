#pragma once

#include <SFML/Graphics.hpp>
#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"
#include "TileType.hpp"

class Model : public UpdateableGroup {
public:
	Model();

	/*
		Initializes the level's 2D tile array (mapTiles) from a given image file.
	*/
	void readMapTiles(std::string filepath);

private:
	/*
		Returns the tile type associated with a color in the map_tiles image.
		These associations are hard-coded into this function.
	*/
	static TileType parseColor(const sf::Color&);

	int levelHeight, levelWidth;
	TileType** mapTiles;
};