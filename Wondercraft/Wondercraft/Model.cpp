#include "Model.hpp"

#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

#include "BasicTile.hpp"

Model::Model() {
	player = new Player();
	gameState = GameState::TITLE;
	transitionTime = 0;
}

Model::~Model() {
	//delete player
	delete player;
	player = NULL;
	
	this->cleanLevel();
}

void Model::startGame() {
	//reset inventory
	for (int x = 0; x < invWidth; x++) {
		for (int y = 0; y < invHeight; y++) {
			inventory[x][y] = ItemType::NONE;
		}
	}

	//reset player equipment
	player->equipment[0] = ItemType::BASIC_HAT;
	player->equipment[1] = ItemType::BASIC_ROBE;
	player->equipment[2] = ItemType::BASIC_STAFF;

	//set up the first level
	currLevel = 1;
	resetLevel(true);
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

void Model::resetLevel(bool resetItems) {
	gameState = GameState::TRANSITION;

	cleanLevel(resetItems);

	//convert currLevel to a string and read the corresponding level files
	std::stringstream ss;
	ss << currLevel;
	readMapTiles("assets/map_tiles/level_" + ss.str() + ".png");
	readMapData("assets/map_data/level_" + ss.str() + ".txt", resetItems);

	player->setPosition(playerSpawn);
	player->setVelocity(sf::Vector2f(0, 0));
	player->resetHealth();
}

void Model::nextLevel() {
	currLevel++;
	resetLevel(true);
}

void Model::readMapTiles(std::string filepath) {
	//load the image to read tiles from
	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	//store the dimensions of the level
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
			//get pixel color
			sf::Color pixelColor = terrainImage.getPixel(x, y);

			//create a new tile based on the pixel color
			mapTiles[x][y] = parseColor(pixelColor);

			if (mapTiles[x][y] != NULL) {
				//position the tile in the game world
				mapTiles[x][y]->setPosition(sf::Vector2f(x + 0.5, y + 0.5));
			}
		}
	}
}

Entity* Model::parseColor(const sf::Color& c) {
	//stone is the only tile currently implemented
	if (c == sf::Color::Black) return new BasicTile(TileType::STONE);
	else return NULL;
}

void Model::readMapData(std::string filepath, bool includeItems) {
	std::ifstream in(filepath);
	std::string line;
	while (std::getline(in, line)) {
		int colonPos = line.find(':');
		//skip this line if it is empty or has no colon
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
	//compare the key with the following cases

	if (key == "level_name") {
		//set the level name
		this->levelName = args[0];

		return true;
	}

	else if (key == "tile_set") {
		//set the tile set
		this->tileSet = args[0];

		return true;
	}

	else if (key == "player_spawn") {
		//set the player spawn
		this->playerSpawn.x = atof(args[0].c_str());
		this->playerSpawn.y = atof(args[1].c_str());

		return true;
	}

	else if (key == "entity") {
		//create an entity according to the entity function
		entityInitFunctions(args[0], args + 1, numArgs - 1);
		return true;
	}

	else if (key == "item") {
		//add an item to the world
		items.push_back(new LevelItem(ItemType::stringToEnum(args[0]), sf::Vector2f(atof(args[1].c_str()), atof(args[2].c_str()))));
		return true;
	}

	else return false;
}

bool Model::entityInitFunctions(std::string key, std::string* args, int numArgs) {
	//compare the key with the following cases

	if (key == "goober") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), EnemyType::GOOBER, sf::Vector2f(2.5, 1.5)));
		return true;
	}
	else if (key == "ghostie") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), EnemyType::GHOST, sf::Vector2f(1.5, 2.5)));
		return true;
	}
	else if (key == "goblin") {
		enemies.push_back(new Enemy(sf::Vector2f(atof(args[0].c_str()), atof(args[1].c_str())), EnemyType::GOBLIN, sf::Vector2f(1.5, 2.5)));
		return true;
	}

	else return false;
}

void Model::update(float deltaTime) {
	//PLAYING STATE
	if (gameState == GameState::PLAYING) {
		//apply gravity to the player
		if (!playerIsGrounded())
			player->setVelocity(player->getVelocity() + sf::Vector2f(0, 16)*deltaTime);

		//update the player's position (and do collision checking)
		player->update(deltaTime, this);

		//player death
		if (player->getHealth() < 0 || player->getPosition().y >= 16) {
			resetLevel(false);
		}

		//player beats level
		if (player->getPosition().x >= levelWidth - 1) {
			if (currLevel == 4)
				gameState = GameState::END;
			else nextLevel();
		}


		//update player projectiles
		for (int i = 0; i < playerProjectiles.size(); i++) {
			playerProjectiles[i]->update(deltaTime, this);
		}

		//update enemy projectiles
		for (int i = 0; i < enemyProjectiles.size(); i++) {
			enemyProjectiles[i]->update(deltaTime, this);
		}

		//update enemies
		for (int i = 0; i < enemies.size(); i++) {
			Enemy* currentEnemy = dynamic_cast <Enemy*>(enemies[i]);
			currentEnemy->update(deltaTime, player, this);
		}

		//update camera position
		camera = player->getPosition();
	}

	//TRANSITION STATE
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

void Model::pickUp() {
	//loop through the items in the level
	for (int i = 0; i < items.size(); i++) {
		LevelItem* item = items[i];

		//check if the current item is close enough to pick up

		sf::Vector2f diff = player->getPosition() - item->position;
		float distSq = diff.x * diff.x + diff.y * diff.y;

		if (distSq < pickupDistSq) {
			//look for an empty place in the inventory
			for (int y = 0; y < invHeight; y++) {
				for (int x = 0; x < invWidth; x++) {
					if (inventory[x][y] == ItemType::NONE) {
						//add to inventory
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