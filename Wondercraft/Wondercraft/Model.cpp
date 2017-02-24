#include "Model.hpp"

#include <iostream>
#include <fstream>

Model::Model() {
	initTyleTypeMap();
}

void Model::readMapTiles(std::string filepath) {

	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	levelHeight = terrainImage.getSize().y;
	levelWidth = terrainImage.getSize().x;

	//initialize the array of tile types
	mapTiles = new Tile_Type*[levelHeight];
	for (int i = 0; i < levelHeight; i++) {
		mapTiles[i] = new Tile_Type[levelWidth];
	}
	
	sf::Color pixelColor;

	for (int i = 0; i < levelHeight; i++) {
		for (int j = 0; j < levelWidth; j++) {
			pixelColor = terrainImage.getPixel(j, i);
			mapTiles[i][j] = tileConversion[pixelColor];
		}
	}
}

void Model::initTyleTypeMap() {
	tileConversion[sf::Color::Black] = Stone;
}