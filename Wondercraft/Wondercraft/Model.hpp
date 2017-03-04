#pragma once

#include <SFML/Graphics.hpp>
#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"
#include "TileType.hpp"
#include "Player.hpp"

class Model : public UpdateableGroup {
public:
	Model();

	sf::Transformable camera;

	/*
		Initializes the level's 2D tile array (mapTiles) from a given image file.
	*/
	void readMapTiles(std::string filepath);

	/*
		Initializes the level's entities and other properties from a given text file.
	*/
	void readMapData(std::string filepath);

private:
	static std::string trim(std::string&);

	/*
		Returns the tile type associated with a color in the map_tiles image.
		These associations are hard-coded into this function.
	*/
	static TileType parseColor(const sf::Color&);

	/*
		Calls the appropriate initalizer function based on the keys found in the map data file.
		These keys are hard-coded here
	*/
	bool mapInitFunctions(std::string, std::string*, int numArgs);

	/*
		Calls the appropriate initalizer function based on the arguments found on lines starting with 'entity' in the map data file.
		These keys are hard-coded here
	*/
	bool entityInitFunctions(std::string, std::string*, int numArgs);


	int levelHeight, levelWidth;

	/*
		Values used for initalizing and mainting the level data
	*/
	std::string level_name;
	std::string background;
	std::string tile_set;

	sf::Vector2f playerSpawn;

	Player* player;


	//Map tile data read in from the map_tiles file
	TileType** mapTiles;
};