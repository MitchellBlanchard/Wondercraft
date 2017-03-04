#include "View.hpp"
#include <iostream>
#include <cmath>

View::View(Model* model) {

	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");
	
	this->model = model;

	model->camera.x = windowSize.x / 2;
	model->camera.y = windowSize.y / 2;

	levelTextures = TextureLoader("assets/tilesets/meadowTiles/");

	initSpriteArray();

	background.setTexture(*(levelTextures.get("bg.png")));
}

void View::initSpriteArray() {
	//initialize the sprites
	int numRows = int(ceil(windowSize.y / TILE_SIZE) + 1);
	int numCols = int(ceil(windowSize.x / TILE_SIZE) + 1);

	displaySprites.resize(numRows);
	//std::cout << numCols << std::endl;
	for (int i = 0; i < displaySprites.size(); i++) {
		displaySprites[i].resize(numCols);
	}

	for (int row = 0; row < displaySprites.size(); row++) {
		for (int col = 0; col < displaySprites[row].size(); col++) {
			displaySprites[row][col].setPosition(TILE_SIZE * col, TILE_SIZE * row);
			displaySprites[row][col].setTexture(*(getTexture(row, col)));
		}
	}
}

sf::Texture* View::getTexture(int r, int c) {
	switch (model->mapTiles[r][c]) {

		case STONE:
			return levelTextures.get("stone.png");
			std::cout << "Stone" << std::endl;
			break;

		default:
			return levelTextures.get("nullTile.png");
			break;
	}
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::updateTiles() {
	sf::Vector2f startingCoord;
	startingCoord.x = model->camera.x - (windowSize.x/2 - TILE_SIZE/2);
	startingCoord.y = model->camera.y - (windowSize.y/2 - fmod(windowSize.y, TILE_SIZE)/2);

	int currentTileX = int(floor(startingCoord.x / TILE_SIZE));
	//std::cout << currentTileX << std::endl;
	int currentTileY = int(floor(startingCoord.y / TILE_SIZE));

	//initialize the sprites
	int numRows = int(ceil(windowSize.y / TILE_SIZE) + 1);
	int numCols = int(ceil(windowSize.x / TILE_SIZE) + 1);
	
	float xOffset, yOffset;
	xOffset = fmod(model->camera.x, TILE_SIZE);
	yOffset = fmod(model->camera.y, TILE_SIZE);

	for (int row = 0; row < displaySprites.size(); row++) {
		for (int col = 0; col < displaySprites[row].size(); col++) {
			displaySprites[row][col].setPosition(TILE_SIZE * (col), TILE_SIZE * (row));
			displaySprites[row][col].move(xOffset, -yOffset);
			displaySprites[row][col].setTexture(*(getTexture(row + currentTileY, col - currentTileX)));
		}
	}
}

void View::render() {
	window.clear();
	
	updateTiles();
	//create a new render state
	//sf::RenderStates cameraState = model->camera.getInverseTransform();

	//draw the map sprites
	
	window.draw(background);

	for (int i = 0; i < displaySprites.size(); i++) {
		for (int j = 0; j < displaySprites[i].size(); j++) {
			window.draw(displaySprites[i][j]);
		}
	}
    
	window.display();
}