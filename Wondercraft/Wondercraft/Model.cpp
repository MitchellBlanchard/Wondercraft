#include "Model.hpp"

#include <string>
#include <iostream>
#include <fstream>

Model::Model() {
	readMapTiles("assets/map_tiles/test_level_1.png");
	readMapData("assets/map_data/test_level_1.txt");
}

void Model::readMapTiles(std::string filepath) {

	sf::Image terrainImage;
	terrainImage.loadFromFile(filepath);

	levelHeight = terrainImage.getSize().y;
	levelWidth = terrainImage.getSize().x;

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
		int argStart = 0;
		std::string* args = new std::string[numArgs];
		for (int i = 0; i < numArgs-1; i++) {
			int commaPos = value.find(',');
			args[i] = trim(value.substr(argStart, commaPos - argStart));
			argStart = commaPos + 1;
		}
		args[numArgs - 1] = trim(value.substr(argStart));

		////////////////////////////////////////////// here we should check the key with a switch or if-else-if statements
		////////////////////////////////////////////// then we should call functions etc. accordingly, using our arguments list
		int rc = mapInitFunctions(key, args);

		delete[] args;
	}
	in.close();
}

std::string Model::trim(std::string& str) {
	return str.substr(str.find_first_not_of(' '), str.find_last_not_of(' ') - str.find_first_not_of(' '));
}

int Model::mapInitFunctions(std::string key, std::string* args) {
	//check the key with hardcoded values

	if (key == "level_name") {
		//set the level name
		this->level_name = args[0];
	}

	else if (key == "background") {
		//set the background
		this->background = args[0];
	}

	else if (key == "tile_set ") {
		//set the tile set
		this->tile_set = args[0];
	}

	else if (key == "left_wall") {
		//call wall function
	}

	else if (key == "right_wall") {
		//call wall function
	}

	else if (key == "player_spawn") {
		//set the player spawn
		this->playerSpawn.x = atoi(args[0].c_str()); //the x spawn value form the map data file
		this->playerSpawn.y = atoi(args[1].c_str()); //the y spawn value from the map data file
	}

	else if (key == "entity") {
		//call entity function
	}
}