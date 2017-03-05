#include "View.hpp"
#include <iostream>
#include <cmath>

View::View(Model* model) {
	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");
	
	this->model = model;

	model->camera.x = windowSize.x / 2;
	model->camera.y = windowSize.y / 2;

	levelTextures = new TextureLoader("assets/tilesets/meadowTiles/");
	spriteTextures = new TextureLoader("assets/sprites/");

	initSpriteArray();

	background.setTexture(*(levelTextures->get("bg.png")));
	
	player.setTexture(*(spriteTextures->get("player.png")));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
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
	if(r < 0 || r >= model->levelHeight || c < 0 || c >= model->levelWidth)
		return levelTextures->get("nullTile.png");

	switch (model->mapTiles[r][c]) {

		case STONE:
			return levelTextures->get("stone.png");
			std::cout << "Stone" << std::endl;
			break;

		default:
			return levelTextures->get("nullTile.png");
			break;
	}
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::updateTiles() {
	sf::Vector2f startingCoord;
	startingCoord.x = -model->camera.x + (windowSize.x/2 - TILE_SIZE/2);
	startingCoord.y = model->camera.y - (windowSize.y/2 - fmod(windowSize.y, TILE_SIZE)/2);

	int currentTileX = int(floor(startingCoord.x / TILE_SIZE));
	int currentTileY = int(floor(startingCoord.y / TILE_SIZE));
	
	float xOffset, yOffset;
	xOffset = -fmod(model->camera.x, TILE_SIZE);
	yOffset = fmod(model->camera.y, TILE_SIZE);

	for (int row = 0; row < displaySprites.size(); row++) {
		for (int col = 0; col < displaySprites[row].size(); col++) {
			displaySprites[row][col].setPosition(TILE_SIZE * (col), TILE_SIZE * (row) + 14);
			displaySprites[row][col].move(xOffset, -yOffset);
			displaySprites[row][col].setTexture(*(getTexture(row + currentTileY, col - currentTileX - 2)));
		}
	}
}

void View::render() {
	//std::cout << "camera :" << model->camera.x << model->camera.y << std::endl;
	window.clear();
	
	updateTiles();

	//create a new render state
	sf::RenderStates cameraState;
	cameraState.transform.translate(windowSize.x/2 - model->camera.x + TILE_SIZE / 2, windowSize.y/2 - model->camera.y);

	//draw the map sprites
	
	window.draw(background);

	for (int i = 0; i < displaySprites.size(); i++) {
		for (int j = 0; j < displaySprites[i].size(); j++) {
			window.draw(displaySprites[i][j]);
		}
	}

	player.setPosition(model->player->getPosition().x * TILE_SIZE, model->player->getPosition().y * TILE_SIZE);
	window.draw(player, cameraState);

	for (int i = 0; i < model->playerProjectiles.size(); i++) {
		sf::Sprite projectile;
		projectile.setTexture(*spriteTextures->get("fireball.png"));
		projectile.setPosition(model->playerProjectiles[i]->getPosition() * TILE_SIZE);
		window.draw(projectile, cameraState);
	}

	for (int i = 0; i < model->enemies.size(); i++) {
		sf::Sprite enemy;
		enemy.setTexture(*spriteTextures->get("goober.png"));
		enemy.setPosition(model->enemies[i]->getPosition() * TILE_SIZE);
		window.draw(enemy, cameraState);
	}
    
	window.display();
}