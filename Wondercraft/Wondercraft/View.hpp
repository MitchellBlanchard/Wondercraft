#pragma once

#include "Model.hpp"
#include "TextureLoader.hpp"
#include "DrawableGroup.hpp"

#include <math.h>

class View {
public:
	View(Model*);

	Model* model;

	const float TILE_SIZE = 64;

	sf::RenderWindow& getWindow();
	sf::Texture* getTexture(int, int);

	sf::Sprite background;
	sf::Sprite player;

	TextureLoader* levelTextures;
	TextureLoader* spriteTextures;

	void render();
	void updateTiles();

	std::vector<std::vector<sf::Sprite>> displaySprites;

	sf::Vector2f windowSize;
private:

	void initSpriteArray();

	sf::RenderWindow window;

	
};