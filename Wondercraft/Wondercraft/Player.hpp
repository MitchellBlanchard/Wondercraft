#pragma once

#include <SFML/Graphics.hpp>
#include "TileType.hpp"
#include "RectangleEntity.hpp"

class Player : public RectangleEntity{
public:
	Player(sf::Vector2f spawn);
	void updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight);

	sf::Vector2f velocity;

	const float PROJECTILE_MAX_COOLDOWN = 1;
	float projectileCooldown;
private:
	
};