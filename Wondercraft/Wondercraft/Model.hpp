#pragma once

#include <SFML/Graphics.hpp>

#include "TileType.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "ItemType.hpp"
#include "LevelItem.hpp"

// States used to determine the behaviour of the update() function
namespace GameState {
	enum GameState {
		PLAYING,
		INVENTORY,
		TITLE,
		TRANSITION,
		END
	};
}

// Part of the Model-View-Controller architecture.
// Is acted on by the controller and is monitored by the view.
class Model {
public:
	Model();
	~Model();

	// Handles updates during all game states.
	void update(float deltaTime);

	// Initializes the level's 2D tile array (mapTiles) from a given image file.
	void readMapTiles(std::string filepath);

	// Initializes the level's entities and other properties from a given text file.
	// Optionally, items can be omitted. This option is used when resetting the same level.
	void readMapData(std::string filepath, bool includeItems = true);

	// Returns true if the player is standing on a tile
	bool playerIsGrounded();

	// If any items are near the player, one of them is
	// removed from the map and added to the player inventory.
	void pickUp();



	// Used to determine the control flow of the game
	GameState::GameState gameState;

	// Center of viewport
	sf::Vector2f camera;

	// Tile grid (static platforms)
	Entity*** mapTiles;
	int levelHeight, levelWidth;

	// Moving entities
	Player* player;
	std::vector<Entity*> enemies;
	std::vector<Projectile*> playerProjectiles;
	std::vector<Projectile*> enemyProjectiles;

	// Items on the map
	std::vector<LevelItem*> items;

	// The max distance at which the player can pick up an item, squared
	const float pickupDistSq = 1.5*1.5;

	static const int invWidth = 10, invHeight = 3;
	ItemType::ItemType inventory [invWidth][invHeight];
	Menu menu;

	int currLevel;
	

	void startGame();
	void cleanLevel(bool cleanItems = true);
	void resetLevel(bool resetItems);
	void nextLevel();

	float transitionTime;

	std::string tileSet;

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
	std::string levelName;

	sf::Vector2f playerSpawn;
};