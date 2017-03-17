#include "Projectile.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Vector2f spawn, sf::Vector2f playerVec, sf::Vector2f mouseLoc, float TILE_SIZE) : RectangleEntity(spawn, sf::Vector2f(1.5,2.5)) {
	
	sf::Vector2f mouseVector = sf::Vector2f((float)mouseLoc.x*(float)TILE_SIZE, (float)mouseLoc.y*(float)TILE_SIZE);
	sf::Vector2f diffVector = mouseVector - playerVec;
	
	float magnitude = sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));
	velocity = sf::Vector2f((diffVector.x / magnitude)*5, (diffVector.y / magnitude)*5);
}

void Projectile::update(float deltaTime, Model* model) {
	position += (velocity * deltaTime);
}


/*
bool Projectile::updatePosition(float dt, TileType** tiles, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies) {
	position += (velocity * dt);
	sf::Vector2f checkPoint = position;
	for (int i = 0; i < enemies.size(); i++) {
		if (checkPoint.x > enemies[i]->position.x - enemies[i]->getSize().x/2
			&& checkPoint.y > enemies[i]->position.y - enemies[i]->getSize().y/2
			&& checkPoint.x < enemies[i]->position.x + enemies[i]->getSize().x/2
			&& checkPoint.y < enemies[i]->position.y + enemies[i]->getSize().y/2) {
			enemies.erase(enemies.begin() + i);
			return false;
		}
	}


	if (checkPoint.x > 0 && checkPoint.y > 0 && checkPoint.x < tilesWidth && checkPoint.y < tilesHeight) {
		TileType& tile = tiles[int(checkPoint.y)][int(checkPoint.x)];
		if (tile != TileType::NONE) {
			return false;
		}
	}
	return true;
}*/