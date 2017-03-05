#pragma once

#include <SFML/Graphics.hpp>
#include "TileType.hpp"

class Player : public sf::Transformable {
public:
	Player(sf::Vector2f spawn);
	void updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight);

	sf::Vector2f velocity;
	float rx, ry;

	const float PROJECTILE_MAX_COOLDOWN = 1;
	float projectileCooldown;
private:
	
};