#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.hpp"
#include "Enemy.hpp"
#include "RectangleEntity.hpp"
#include <cmath>


class Projectile : public RectangleEntity {
public:
	Projectile(sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
	//bool updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies);

	void update(float, Model*);

	sf::Vector2i mouseLoc;

private:

};