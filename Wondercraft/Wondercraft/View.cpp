#include "View.hpp"
#include <iostream>
#include <cmath>

View::View(Model* model) {
	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");
	
	this->model = model;

	//model->camera.x = (windowSize.x / 2)/TILE_SIZE;
	//model->camera.y = (windowSize.y / 2)/TILE_SIZE;

	levelTextures = new TextureLoader("assets/tilesets/meadowTiles/");
	spriteTextures = new TextureLoader("assets/sprites/");
	menuTextures = new TextureLoader("assets/menus/");
	 
	initSpriteArray();

	initMenuArray();

	background.setTexture(*(levelTextures->get("bg.png")));
	
	player.setTexture(*(spriteTextures->get("player.png")));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);

	menu.setTexture(*(menuTextures->get("1.png")));
	selected.setTexture(*(menuTextures->get("3.png")));

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

void View::initMenuArray() {
	menuSquares1.resize(3);
	for (int row = 0; row < menuSquares1.size(); row++) {
		menuSquares1[row].resize(1);
	}

	for (int row = 0; row < menuSquares1.size(); row++) {
		for (int col = 0; col < menuSquares1[row].size(); col++) {
			menuSquares1[row][col].setPosition(SQUARE_SIZE_X * col + 317 + col * 5, SQUARE_SIZE_Y * row + 3 + row * 2);
			menuSquares1[row][col].setTexture(*(menuTextures->get("tile.png")));
		}
	}

	menuSquares2.resize(1);
	for (int row = 0; row < menuSquares2.size(); row++) {
		menuSquares2[row].resize(3);
	}

	for (int row = 0; row < menuSquares2.size(); row++) {
		for (int col = 0; col < menuSquares2[row].size(); col++) {
			menuSquares2[row][col].setPosition(SQUARE_SIZE_X * col + 528 + col * 57, SQUARE_SIZE_Y * row + 136);// +row * 2);
			menuSquares2[row][col].setTexture(*(menuTextures->get("tile.png")));
		}
	}


	menuSquares3.resize(3);
	for (int row = 0; row < menuSquares3.size(); row++) {
		menuSquares3[row].resize(10);
	}

	for (int row = 0; row < menuSquares3.size(); row++) {
		for (int col = 0; col < menuSquares3[row].size(); col++) {
			menuSquares3[row][col].setPosition(SQUARE_SIZE_X * col + 84 + col * 5, SQUARE_SIZE_Y * row + 280 +row * 2);
			menuSquares3[row][col].setTexture(*(menuTextures->get("tile.png")));
		}
	}

	selected.setPosition(84, 280);
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
	sf::Vector2f startingCoord = getStartingPos();
	//startingCoord.x = model->camera.x - ((windowSize.x/2)/TILE_SIZE);
	//startingCoord.y = model->camera.y - ((windowSize.y/2)/TILE_SIZE);

	int currentTileX = int(floor(startingCoord.x));
	int currentTileY = int(floor(startingCoord.y));
	
	float xOffset, yOffset;
	//xOffset = yOffset = 0;
	
	xOffset = -fmod(startingCoord.x, 1);
	if (xOffset > 0) {
		xOffset--;
	}

	yOffset = -fmod(startingCoord.y, 1);
	if (yOffset > 0) {
		yOffset--;
	}

	//std::cout << currentTileX << " : " << currentTileY << std::endl;
	//std::cout << "Starting Coord: " << startingCoord.x << " : " << startingCoord.y << " : "  << ", Current Tile: " << currentTileX << " : " << currentTileY  << ", Offset: " << xOffset << " : " << yOffset<< std::endl;
	for (int row = 0; row < displaySprites.size(); row++) {
		for (int col = 0; col < displaySprites[row].size(); col++) {
			displaySprites[row][col].setPosition(TILE_SIZE * (col), TILE_SIZE * (row));
			displaySprites[row][col].move(xOffset*TILE_SIZE, yOffset*TILE_SIZE);
			displaySprites[row][col].setTexture(*(getTexture(row + currentTileY, col + currentTileX )));
		}
	}
}

sf::Vector2f View::getStartingPos() {
	sf::Vector2f startingCoord;
	startingCoord.x = model->camera.x - ((windowSize.x / 2) / TILE_SIZE);
	startingCoord.y = model->camera.y - ((windowSize.y / 2) / TILE_SIZE);

	return startingCoord;
}

void View::render(int gameState) {
	//std::cout << "camera :" << model->camera.x << model->camera.y << std::endl;
	window.clear();
	
	updateTiles();

	//create a new render state
	sf::RenderStates cameraState;
	//cameraState.transform.translate(/*windowSize.x/2*/  -model->camera.x, /*windowSize.y/2*/  -model->camera.y);

	//draw the map sprites
	
	window.draw(background);

	for (int i = 0; i < displaySprites.size(); i++) {
		for (int j = 0; j < displaySprites[i].size(); j++) {
			window.draw(displaySprites[i][j]);
		}
	}

	sf::Vector2f startingCoord = getStartingPos();

	player.setPosition((model->player->position.x - startingCoord.x) * TILE_SIZE, (model->player->position.y - startingCoord.y)* TILE_SIZE);
	//std::cout << player.getPosition().x << " : " << player.getPosition().y << std::endl;
	window.draw(player, cameraState);

	for (int i = 0; i < model->playerProjectiles.size(); i++) {
		sf::Sprite projectile;
		projectile.setTexture(*spriteTextures->get("fireball.png"));
		projectile.setPosition((model->playerProjectiles[i]->position - startingCoord) * TILE_SIZE);
		window.draw(projectile/*, cameraState*/);
	}

	for (int i = 0; i < model->enemies.size(); i++) {
		sf::Sprite enemy;
		enemy.setTexture(*spriteTextures->get("goober1.png"));
		enemy.setPosition(( model->enemies[i]->position - startingCoord) * TILE_SIZE);
		window.draw(enemy/*, cameraState*/);
	}

	if (model->gameState == 2) { //drawing the pause menu
		window.draw(menu);

		for (int i = 0; i < menuSquares1.size(); i++) {
			for (int j = 0; j < menuSquares1[i].size(); j++) {
				window.draw(menuSquares1[i][j]);
			}
		}

		for (int i = 0; i < menuSquares2.size(); i++) {
			for (int j = 0; j < menuSquares2[i].size(); j++) {
				window.draw(menuSquares2[i][j]);
			}
		}

		for (int i = 0; i < menuSquares3.size(); i++) {
			for (int j = 0; j < menuSquares3[i].size(); j++) {
				window.draw(menuSquares3[i][j]);
			}
		}

		window.draw(selected);
	}
	//std::cout << model->gameState << std::endl;
	std::cout << "X: " << selected.getPosition().x << ", Y: " << selected.getPosition().y << std::endl;
    
	window.display();
}