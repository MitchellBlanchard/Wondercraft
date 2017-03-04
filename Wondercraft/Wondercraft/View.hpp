#pragma once

#include "Model.hpp"
#include <math.h>

class View {
public:
	View(const Model*);

	const float TILE_SIZE = 64;

	sf::RenderWindow& getWindow();

	void render();

	std::vector<std::vector<sf::Sprite>> displaySprites;

private:

	const Model* model;

	void initSpriteArray();

	sf::RenderWindow window;

	sf::Vector2f windowSize;
};