#pragma once

#include "Model.hpp"
#include "TextureLoader.hpp"
#include "DrawableGroup.hpp"
#include "Enemy.hpp"

#include <math.h>

class View {
public:
	View(Model*);

	Model* model;

	const float TILE_SIZE = 64;

	const float SQUARE_SIZE_X = 73;
	const float SQUARE_SIZE_Y = 84;

	sf::RenderWindow& getWindow();
	sf::Texture* getTexture(int, int);

	sf::Sprite background;
	//sf::Sprite player;
	sf::Sprite title;
	sf::Sprite end;

	sf::Sprite healthBar;
	sf::Sprite health;

	sf::Sprite playerHat;
	sf::Sprite playerRobe;
	sf::Sprite playerStaff;

	//the menu bg and the selected square
	sf::Sprite menu;
	sf::Sprite selected;

	TextureLoader* levelTextures;
	TextureLoader* spriteTextures;
	TextureLoader* menuTextures;
	TextureLoader* itemTextures;

	void render();
	void updateTiles();

	sf::Vector2f getStartingPos();

	std::vector<std::vector<sf::Sprite>> displaySprites;

	//these three hold the squares in the menu
	std::vector<std::vector<sf::Sprite>> menuSquares1;
	std::vector<std::vector<sf::Sprite>> menuSquares2;
	std::vector<std::vector<sf::Sprite>> menuSquares3;

	//transition garbo
	sf::Sprite map;
	sf::Sprite icon;

	sf::Vector2f windowSize;
private:

	void initSpriteArray();
	void initMenuArray();

	void playTransition();

	sf::RenderWindow window;
};