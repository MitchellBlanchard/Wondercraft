#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.hpp"
#include "Enemy.hpp"
#include "RectangleEntity.hpp"

class Projectile : public RectangleEntity {
public:
	Projectile(sf::Vector2f spawn);
	bool updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies);

	sf::Vector2f velocity;

private:

};