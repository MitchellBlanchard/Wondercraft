#pragma once

#include <SFML/Graphics.hpp>
#include "TileType.hpp"

class Player : public sf::Transformable {
public:
	Player(sf::Vector2f spawn);
	void updatePosition(float dt, TileType**);

private:
	float rx, ry;
	sf::Vector2f velocity;
};