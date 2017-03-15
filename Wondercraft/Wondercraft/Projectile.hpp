#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"

class Projectile : public Entity {
public:
	Projectile(sf::Vector2f spawn);
	bool updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies);

	float collisionCalc(float deltaTime, Entity&);

	float rx, ry;

private:

};