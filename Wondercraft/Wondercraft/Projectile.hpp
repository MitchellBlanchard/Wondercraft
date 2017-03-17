#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.hpp"
#include "Enemy.hpp"
#include "RectangleEntity.hpp"
#include <cmath>


class Projectile : public RectangleEntity {
public:
	const int FIREBALL = 1;
	const int FIRE_BOMB = 2;
	const float TILE_SIZE;

	Projectile(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, int);
	//bool updatePosition(float dt, TileType**, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies);

	void update(float, Model*);
	void setBehaviour();

	void explode();

	int projectileType;
private:
	sf::Vector2f mouseVector;
	sf::Vector2f mouseLoc;
	sf::Vector2f startingPos;
	sf::Vector2f diffVector;
	float magnitude;
};