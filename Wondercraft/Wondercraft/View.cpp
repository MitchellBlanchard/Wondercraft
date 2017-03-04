#include "View.hpp"
#include <iostream>
View::View(const Model* model) {

	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");

	
	this->model = model;

	levelTextures = TextureLoader("assets/tilesets/meadowTiles/");

	initSpriteArray();

	sf::Transformable thisCamera = model->camera;

}

void View::initSpriteArray() {
	//initialize the sprites
	int numRows = int(ceil(windowSize.y / 64) + 1);
	int numCols = int(ceil(windowSize.x / 64) + 1);

	displaySprites.resize(numRows);

	for (int i = 0; i < displaySprites.size(); i++) {
		displaySprites[i].resize(numCols);
	}

	for (int row = 0; row < displaySprites.size(); row++) {
		for (int col = 0; col < displaySprites[row].size(); col++) {
			displaySprites[row][col].setPosition(64 * col, 64 * row);
			//std::cout << "X: " << displaySprites[row][col].getPosition().x << " Y " << displaySprites[row][col].getPosition().y << std::endl;
			displaySprites[row][col].setTexture(*(getTexture(row, col)));
		}
	}
}

sf::Texture* View::getTexture(int r, int c) {
	switch (model->mapTiles[r][c]) {

		case STONE:
			return levelTextures.get("stone.png");
			std::cout << "Stone" << std::endl;
			//testTexture.loadFromFile("assets/tilesets/meadowTiles/stone.png");
			break;

		default:
			//testTexture.loadFromFile("assets/tilesets/meadowTiles/nullTile.png");
			return levelTextures.get("nullTile.png");
			break;
	}
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::render() {
	window.clear();
	
	//create a new render state
	//sf::RenderStates cameraState = model->camera.getInverseTransform();

	//draw the map sprites
	
	
	for (int i = 0; i < displaySprites.size(); i++) {
		for (int j = 0; j < displaySprites[i].size(); j++) {
			window.draw(displaySprites[i][j]);
		}
	}


	window.display();
}