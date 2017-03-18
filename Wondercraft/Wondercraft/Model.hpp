#pragma once

#include <SFML/Graphics.hpp>
#include "UpdateableGroup.hpp"
#include "DrawableGroup.hpp"
#include "TileType.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "ItemType.hpp"
#include "LevelItem.hpp"

namespace GameState {
	enum GameState {
		PLAYING,
		INVENTORY
	};
}

class Model : public Updateable {
public:
	Model();
	~Model();

	virtual void update(float);

	sf::Vector2f camera;

	/*
		Initializes the level's 2D tile array (mapTiles) from a given image file.
	*/
	void readMapTiles(std::string filepath);

	/*
		Initializes the level's entities and other properties from a given text file.
	*/
	void readMapData(std::string filepath);

	//Map tile data read in from the map_tiles file
	Entity*** mapTiles;
	int levelHeight, levelWidth;

	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> playerProjectiles;
	std::vector<Projectile*> enemyProjectiles;
	std::vector<LevelItem*> items;

	bool playerIsGrounded();

	GameState::GameState gameState;

	ItemType::ItemType inventory [10][3];
	Menu menu;

private:
	static std::string trim(std::string&);

	/*
		Returns the tile type associated with a color in the map_tiles image.
		These associations are hard-coded into this function.
	*/
	static Entity* parseColor(const sf::Color&);

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

	/*
		Values used for initalizing and mainting the level data
	*/
	std::string level_name;
	std::string background;
	std::string tile_set;

	sf::Vector2f playerSpawn;
};