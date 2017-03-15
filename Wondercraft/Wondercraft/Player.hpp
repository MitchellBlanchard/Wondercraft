#pragma once

#include <SFML/Graphics.hpp>
#include "TileType.hpp"
#include "Entity.hpp"

class Player : public Entity {
public:
	Player(sf::Vector2f spawn);
	void updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight);
	float collisionCalc(float deltaTime, Entity&);

	const float PROJECTILE_MAX_COOLDOWN = 1;
	float projectileCooldown;
private:
	
};