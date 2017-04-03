#pragma once

#include "Model.hpp"
#include "TextureLoader.hpp"
#include "Enemy.hpp"

#include <math.h>

// Part of the Model-View-Controller architecture.
// Monitors the model and is monitored by the controller.
class View {
public:
	View(Model*);

	//renders the screen
	void render();

	//called after the game has been initialized in the model
	void initGame();

	//updates the vertex array for the tiles to correspond with the camera position
	void updateTileArray();

	//returns the position top left corner of the viewport in game world (model) coordinates
	sf::Vector2f getTopLeftCorner();

	//returns the negated position of the top left corner of the
	//viewport relative to the tile at that position, measured in pixels
	sf::Vector2f getVertexArrayOffset();


	Model* model;

	//window size in pixels
	sf::Vector2f windowSize;

	//dimension of a single unit in model space (equal to one tile) in pixels
	const float TILE_SIZE = 64;

	//size of the slots in the inventory menu
	const float SQUARE_SIZE_X = 73;
	const float SQUARE_SIZE_Y = 84;

	sf::RenderWindow& getWindow();

	//returns the coordinates within the spritesheet of the texture
	//associated with the tile at the given coordinates in the model
	sf::Vector2i getSpritesheetCoords(int, int);

	sf::VertexArray tileVertices;

	sf::Sprite background;
	sf::Sprite title;
	sf::Sprite end;

	sf::Sprite healthBar; // outer container
	sf::Sprite health;    // red part

	//player sprites
	sf::Sprite playerHat;
	sf::Sprite playerRobe;
	sf::Sprite playerStaff;

	//transition sprites
	sf::Sprite map;
	sf::Sprite icon;

	//inventory menu sprites
	sf::Sprite menu;
	sf::Sprite selected;
	sf::Sprite index;

	//texture loaders each with different root directories
	TextureLoader* levelTextures;
	TextureLoader* spriteTextures;
	TextureLoader* menuTextures;
	TextureLoader* itemTextures;

	//empty texture used when an item is not meant to be drawn
	sf::Texture EMPTY_ITEM_TEXTURE;

	//these three hold the squares in the menu
	sf::Sprite equipmentSquares [3];
	sf::Sprite craftingSquares  [3];
	sf::Sprite inventorySquares [10][3];

private:
	void initVertexArray();
	void initMenuArray();

	void playTransition();

	sf::RenderWindow window;
};