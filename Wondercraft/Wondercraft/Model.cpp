#include "Model.hpp"

#include <iostream>
#include <fstream>

Model::Model() {
	
}

void Model::readTerrain(std::string filename) {

	sf::Image terrainImage;
	terrainImage.loadFromFile(filename);

	level_Height = terrainImage.getSize().y;
	level_Width = terrainImage.getSize().x;

	//initialize the array of tile types
	mapTiles = new Tile_Type*[level_Height];
	for (int i = 0; i < level_Height; i++) {
		mapTiles[i] = new Tile_Type[level_Width];
	}
	
	sf::Color pixelColor;

	for (int i = 0; i < level_Height; i++) {
		for (int j = 0; j < level_Width; j++) {
			pixelColor = terrainImage.getPixel(j, i);
			mapTiles[i][j] = tile_Conversion[pixelColor];
		}
	}
}