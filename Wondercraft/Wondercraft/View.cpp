#include "View.hpp"

#include <iostream>
#include <cmath>

#include "Tile.hpp"

View::View(Model* model) {
	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");
	
	this->model = model;

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
	int numCols = int(ceil(windowSize.x / TILE_SIZE) + 1);
	int numRows = int(ceil(windowSize.y / TILE_SIZE) + 1);

	displaySprites.resize(numCols);
	for (int i = 0; i < displaySprites.size(); i++) {
		displaySprites[i].resize(numRows);
	}

	for (int x = 0; x < displaySprites.size(); x++) {
		for (int y = 0; y < displaySprites[x].size(); y++) {
			displaySprites[x][y].setPosition(TILE_SIZE * x, TILE_SIZE * y);
			displaySprites[x][y].setTexture(*(getTexture(x, y)));
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

sf::Texture* View::getTexture(int x, int y) {
	if(x < 0 || x >= model->levelWidth || y < 0 || y >= model->levelHeight)
		return levelTextures->get("nullTile.png");

	Tile* e = dynamic_cast<Tile*>(model->mapTiles[x][y]);
	
	if (e == NULL) {
		return levelTextures->get("nullTile.png");
	}
	else if(e->type == TileType::STONE){
		return levelTextures->get("stone.png");
	}
	else {
		return levelTextures->get("nullTile.png");
	}
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::updateTiles() {
	sf::Vector2f startingCoord = getStartingPos();

	int currentTileX = int(floor(startingCoord.x));
	int currentTileY = int(floor(startingCoord.y));
	
	float xOffset, yOffset;
	
	xOffset = -fmod(startingCoord.x, 1);
	if (xOffset > 0) {
		xOffset--;
	}

	yOffset = -fmod(startingCoord.y, 1);
	if (yOffset > 0) {
		yOffset--;
	}

	for (int x = 0; x < displaySprites.size(); x++) {
		for (int y = 0; y < displaySprites[x].size(); y++) {
			displaySprites[x][y].setPosition((x + xOffset) * TILE_SIZE, (y + yOffset) * TILE_SIZE);
			displaySprites[x][y].setTexture(*getTexture(x + currentTileX, y + currentTileY));
		}
	}
}

sf::Vector2f View::getStartingPos() {
	sf::Vector2f startingCoord;
	startingCoord.x = model->camera.x - ((windowSize.x / 2) / TILE_SIZE);
	startingCoord.y = model->camera.y - ((windowSize.y / 2) / TILE_SIZE);

	return startingCoord;
}

void View::render() {
	window.clear();
	
	updateTiles();

	//create a new render state for the camera displacement
	sf::RenderStates cameraState;
	cameraState.transform.translate(-getStartingPos() * TILE_SIZE);
	//std::cout << -getStartingPos().x * TILE_SIZE + model->player->position.x * TILE_SIZE << " : " << getStartingPos().y * TILE_SIZE + model->player->position.y * TILE_SIZE << std::endl;

	//draw background	
	window.draw(background);

	//draw tiles
	for (int x = 0; x < displaySprites.size(); x++) {
		for (int y = 0; y < displaySprites[x].size(); y++) {
			window.draw(displaySprites[x][y]);
		}
	}

	//draw player
	player.setPosition(model->player->position * TILE_SIZE);
	window.draw(player, cameraState);

	//draw player projectiles
	for (int i = 0; i < model->playerProjectiles.size(); i++) {
		sf::Sprite projectile;
		projectile.setTexture(*spriteTextures->get("fireball.png"));
		projectile.setPosition(model->playerProjectiles[i]->position * TILE_SIZE);
		window.draw(projectile, cameraState);
	}

	//draw enemies
	for (int i = 0; i < model->enemies.size(); i++) {
		sf::Sprite enemy;
		enemy.setTexture(*spriteTextures->get("goober1.png"));
		enemy.setPosition(model->enemies[i]->position * TILE_SIZE);
		window.draw(enemy, cameraState);
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
	//std::cout << "X: " << selected.getPosition().x << ", Y: " << selected.getPosition().y << std::endl;
    
	window.display();
}