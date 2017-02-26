#include "Model.hpp"

#include <iostream>
#include <fstream>

Model::Model() {
	
}

void Model::readMapTiles(std::string filepath) {

	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	levelHeight = terrainImage.getSize().y;
	levelWidth = terrainImage.getSize().x;

	//initialize the array of tile types
	mapTiles = new TileType*[levelHeight];
	for (int i = 0; i < levelHeight; i++) {
		mapTiles[i] = new TileType[levelWidth];
	}
	
	for (int i = 0; i < levelHeight; i++) {
		for (int j = 0; j < levelWidth; j++) {
			sf::Color pixelColor = terrainImage.getPixel(j, i);
			mapTiles[i][j] = parseColor(pixelColor);
		}
	}
}

TileType Model::parseColor(const sf::Color& c) {
	if (c == sf::Color::Black) return TileType::STONE;
	else return TileType::NONE;
}