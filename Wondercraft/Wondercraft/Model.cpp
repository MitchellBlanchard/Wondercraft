#include "Model.hpp"

#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

#include "BasicTile.hpp"

Model::Model() {
	player = new Player();
	gameState = GameState::TITLE;
}

Model::~Model() {
	//delete player
	delete player;
	player = NULL;
	
	this->cleanLevel();
}

void Model::startGame() {
	//initialize empty inventory
	for (int x = 0; x < inventorySize.x; x++) {
		for (int y = 0; y < inventorySize.y; y++) {
			inventory[x][y] = ItemType::NONE;
		}
	}

	currLevel = 0;
	nextLevel();

	gameState = GameState::TRANSITION;

	transitionTime = 0;
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

void Model::readMapData(std::string filepath, bool includeItems) {
	std::ifstream in(filepath);
	std::string line;
	while (std::getline(in, line)) {
		int colonPos = line.find(':');
		//continue if this line is empty or has no colon
		if (colonPos < 0) continue;

		//split line on the colon into a key and a value
		std::string key = trim(line.substr(0, colonPos));
		if (key == "item" && !includeItems) continue; //don't add items to the map if includeItems is false

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

	else if (key == "tile_set") {
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
		entityInitFunctions(args[0], args + 1, numArgs - 1);
		return true;
	}

	else if (key == "item") {
		items.push_back(new LevelItem(ItemType::stringToEnum(args[0]), sf::Vector2f(atof(args[1].c_str()), atof(args[2].c_str()))));
		return true;
	}

	else return false;
}

bool Model::entityInitFunctions(std::string key, std::string* args, int numArgs) {
	//check the key with hardcoded values

	if (key == "goober") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), 1, sf::Vector2f(2.5, 1.5)));

		return true;
	}
	else if (key == "ghostie") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), 2, sf::Vector2f(1.5, 2.5)));

		return true;
	}
	else if (key == "goblin") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), 3, sf::Vector2f(1.5, 2.5)));

	}

	else return false;
}

void Model::resetLevel() {
	gameState = GameState::TRANSITION;

	cleanLevel(false);

	std::stringstream ss;
	ss << currLevel;
	readMapTiles("assets/map_tiles/level_" + ss.str() + ".png");
	readMapData("assets/map_data/level_" + ss.str() + ".txt", false);

	player->setPosition(playerSpawn);
	player->resetHealth();
}

void Model::nextLevel() {
	currLevel++;

	gameState = GameState::TRANSITION;

	cleanLevel();

	std::stringstream ss;
	ss << currLevel;
	readMapTiles("assets/map_tiles/level_" + ss.str() + ".png");
	readMapData("assets/map_data/level_" + ss.str() + ".txt");

	player->setPosition(playerSpawn);
	player->resetHealth();
}

void Model::update(float deltaTime) {
	if (gameState == GameState::PLAYING) {
		if (!playerIsGrounded())
			player->setVelocity(player->getVelocity() + sf::Vector2f(0, 16)*deltaTime);
		player->update(deltaTime, this);

		if (player->getHealth() < 0 || player->getPosition().y >= 16) {
			resetLevel();
		}

		for (int i = 0; i < playerProjectiles.size(); i++) {
			playerProjectiles[i]->update(deltaTime, this);
		}

		for (int i = 0; i < enemies.size(); i++) {
			Enemy* currentEnemy = dynamic_cast <Enemy*>(enemies[i]);
			currentEnemy->updatePosition(deltaTime, player, this);
		}

		camera = player->getPosition();
		if (player->getPosition().x >= levelWidth - 1) {
			if (currLevel == 4) {
				gameState = GameState::END;
			}
			else nextLevel();
		}
	}
	else if (gameState == GameState::TRANSITION) {
		if (transitionTime < 3) {
			transitionTime += deltaTime;
		}
		else {
			transitionTime = 0;
			gameState = GameState::PLAYING;
		}
	}
}

bool Model::playerIsGrounded() {
	sf::Vector2f checkPoints []{
			sf::Vector2f(player->getLeft() + 0.01, player->getBottom() + 0.01),
			sf::Vector2f(player->getPosition().x, player->getBottom() + 0.01),
			sf::Vector2f(player->getRight() - 0.01, player->getBottom() + 0.01) };
	
	for (int i = 0; i < 3; i++) {
		sf::Vector2f p = checkPoints[i];

		if (p.x > 0 && p.y > 0 && p.x < levelWidth && p.y < levelHeight) {
			Entity* tile = mapTiles[int(floor(p.x))][int(floor(p.y))];
			if (tile != NULL)
				return true;
		}
	}
	return false;
}

void Model::cleanLevel(bool cleanItems) {
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

	//delete items (only if leanItems is true)
	if (cleanItems) {
		for (int i = 0; i < items.size(); i++)
			delete items[i];
		items.clear();
	}

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

void Model::pickUp() {
	//loop through the items in the level
	for (int i = 0; i < items.size(); i++) {
		LevelItem* item = items[i];

		//check if the current item is close enough to pick up
		sf::Vector2f diff = player->getPosition() - item->position;

		float distSq = diff.x * diff.x + diff.y * diff.y;

		if (distSq < pickupDistSq) {
			//look for an empty place in the inventory
			for (int y = 0; y < inventorySize.y; y++) {
				for (int x = 0; x < inventorySize.x; x++) {
					if (inventory[x][y] == ItemType::NONE) {
						//add to inventory
						//std::cout << item->type << std::endl;
						inventory[x][y] = item->type;

						//remove from level
						delete item;
						items.erase(items.begin() + i);

						return;
					}
				}
			}

			return;
		}
	}
}