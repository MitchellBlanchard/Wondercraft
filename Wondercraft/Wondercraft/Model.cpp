#include "Model.hpp"

#include <string>
#include <iostream>
#include <fstream>

Model::Model() {
	readMapTiles("assets/map_tiles/test_level_1.png");
	readMapData("assets/map_data/test_level_1.txt");

	player = new Player(playerSpawn);

	camera.x = 0;
	camera.y = 0;
}

void Model::readMapTiles(std::string filepath) {

	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	levelHeight = terrainImage.getSize().y;
	levelWidth = terrainImage.getSize().x;

	std::cout << levelWidth << std::endl;
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

void Model::update(float dt) {
	//reduce shooting cooldown
	if (player->projectileCooldown > 0)
		player->projectileCooldown -= dt;
	if (player->projectileCooldown < 0)
		player->projectileCooldown = 0;

	if (!playerIsGrounded())
		player->setVelocity(sf::Vector2f(player->getVelocity().x, player->getVelocity().y + 0.6));
	else if (player->getVelocity().y > 0)
		player->setVelocity(sf::Vector2f(player->getVelocity().x,0));
	player->updatePosition(dt, mapTiles, levelWidth, levelHeight);

	for (int i = 0; i < playerProjectiles.size(); i++) {
		if (!playerProjectiles[i]->updatePosition(dt, mapTiles, levelWidth, levelHeight, enemies)) {
			playerProjectiles.erase(playerProjectiles.begin() + i);
		}
	}

	camera.x = player->position.x;
	camera.y = player->position.y;
}

bool Model::playerIsGrounded() {
	sf::Vector2f checkPoint = player->position + sf::Vector2f(0, (player->size.y)/2 + 0.05);
	if (checkPoint.x > 0 && checkPoint.y > 0 && checkPoint.x < levelWidth && checkPoint.y < levelHeight) {
		TileType& tile = mapTiles[int(checkPoint.y)][int(checkPoint.x)];
		return tile != TileType::NONE;
	}
	else return false;
}

void Model::playerShoot() {
	if (player->projectileCooldown == 0) {
		playerProjectiles.push_back(new Projectile(player->position));
		player->projectileCooldown = player->PROJECTILE_MAX_COOLDOWN;
	}
}