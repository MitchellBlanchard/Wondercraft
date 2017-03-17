#include "Model.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "BasicTile.hpp"

Model::Model() {
	readMapTiles("assets/map_tiles/test_level_1.png");
	readMapData("assets/map_data/test_level_1.txt");

	player = new Player(playerSpawn);

	gameState = 1;
}

Model::~Model() {
	//delete player
	delete player;
	player = NULL;

	//delete enemies
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies.clear();

	//delete player projectiles
	for (int i = 0; i < playerProjectiles.size(); i++)
		delete playerProjectiles[i];
	playerProjectiles.clear();

	//delete enemy projectiles
	for (int i = 0; i < enemyProjectiles.size(); i++)
		delete enemyProjectiles[i];
	enemyProjectiles.clear();

	//delete tiles
	for (int x = 0; x < levelWidth; x++) {
		for (int y = 0; y < levelHeight; y++) {
			delete mapTiles[x][y];
		}
		delete[] mapTiles[x];
	}
	delete[] mapTiles;
	mapTiles = NULL;
}

void Model::readMapTiles(std::string filepath) {
	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	levelHeight = terrainImage.getSize().y;
	levelWidth = terrainImage.getSize().x;

	//initialize the array of Entity pointers
	mapTiles = new Entity**[levelWidth];
	for (int x = 0; x < levelWidth; x++) {
		mapTiles[x] = new Entity*[levelHeight];
	}
	
	//fill the array with new tile entities
	for (int x = 0; x < levelWidth; x++) {
		for (int y = 0; y < levelHeight; y++) {
			sf::Color pixelColor = terrainImage.getPixel(x, y);
			mapTiles[x][y] = parseColor(pixelColor);
			if (mapTiles[x][y] != NULL) {
				mapTiles[x][y]->setPosition(sf::Vector2f(x + 0.5, y + 0.5));
			}
		}
	}
}

Entity* Model::parseColor(const sf::Color& c) {
	if (c == sf::Color::Black) return new BasicTile(TileType::STONE);
	else return NULL;
}

void Model::readMapData(std::string filepath) {
	std::ifstream in(filepath);
	std::string line;
	while (std::getline(in, line)) {
		int colonPos = line.find(':');
		//continue if this line is empty or has no colon
		if (colonPos < 0) continue;

		//split line on the colon into a key and a value
		std::string key = trim(line.substr(0, colonPos));
		std::string value = trim(line.substr(colonPos+1));

		//count the number of comma-separated arguments after the colon
		int numArgs = 1;
		for (int i = 0; i < value.size(); i++)
			if (value[i] == ',') numArgs++;

		//split the value on the commas into an array of arguments
		std::string valCopy = value;
		std::string* args = new std::string[numArgs];
		for (int i = 0; i < numArgs-1; i++) {
			int commaPos = valCopy.find(',');
			args[i] = trim(valCopy.substr(0, commaPos));
			valCopy = valCopy.substr(commaPos + 1);
		}
		args[numArgs - 1] = trim(valCopy);

		//initialize values based on the key and arguments
		bool rc = mapInitFunctions(key, args, numArgs);

		delete[] args;
	}
	in.close();
}

std::string Model::trim(std::string& str) {
	return str.substr(str.find_first_not_of(' '), str.find_last_not_of(' ') + 1 - str.find_first_not_of(' '));
}

bool Model::mapInitFunctions(std::string key, std::string* args, int numArgs) {
	//check the key with hardcoded values

	if (key == "level_name") {
		//set the level name
		this->level_name = args[0];

		return true;
	}

	else if (key == "background") {
		//set the background
		this->background = args[0];

		return true;
	}

	else if (key == "tile_set ") {
		//set the tile set
		this->tile_set = args[0];

		return true;
	}

	else if (key == "player_spawn") {
		//set the player spawn
		this->playerSpawn.x = atof(args[0].c_str());
		this->playerSpawn.y = atof(args[1].c_str());

		return true;
	}

	else if (key == "entity") {
		//call entity function
		entityInitFunctions(args[0], args+1, numArgs-1);
		return true;
	}

	else return false;
}

bool Model::entityInitFunctions(std::string key, std::string* args, int numArgs) {
	//check the key with hardcoded values

	if (key == "goober") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str()))));

		return true;
	}

	else return false;
}

void Model::update(float deltaTime) {
	if (!playerIsGrounded())
		player->setVelocity(player->getVelocity() + sf::Vector2f(0, 16)*deltaTime);
	player->update(deltaTime, this);

	for (int i = 0; i < playerProjectiles.size(); i++) {
		playerProjectiles[i]->update(deltaTime, this);
	}
	/*
	for (int i = 0; i < playerProjectiles.size(); i++) {
		if (!playerProjectiles[i]->update(deltaTime, this) {
			playerProjectiles.erase(playerProjectiles.begin() + i);
		}
	}*/

	camera = player->getPosition();
}

bool Model::playerIsGrounded() {
	sf::Vector2f checkPoints []{
			sf::Vector2f(player->getLeft() + 0.01, player->getBottom() + 0.01),
			sf::Vector2f(player->getPosition().x, player->getBottom() + 0.01),
			sf::Vector2f(player->getRight() - 0.01, player->getBottom() + 0.01) };
	
	for (int i = 0; i < sizeof(checkPoints); i++) {
		sf::Vector2f p = checkPoints[i];

		if (p.x > 0 && p.y > 0 && p.x < levelWidth && p.y < levelHeight) {
			Entity* tile = mapTiles[int(floor(p.x))][int(floor(p.y))];
			if (tile != NULL)
				return true;
		}
	}
	return false;
}