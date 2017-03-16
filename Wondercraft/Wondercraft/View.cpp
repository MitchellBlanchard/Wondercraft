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
	 
	initSpriteArray();

	background.setTexture(*(levelTextures->get("bg.png")));
	
	player.setTexture(*(spriteTextures->get("player.png")));
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
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
    
	window.display();
}