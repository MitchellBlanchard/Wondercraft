#include "Projectile.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Vector2f spawn) : RectangleEntity(spawn, sf::Vector2f(1.5,2.5)) {
	velocity.x = 5;
}

bool Projectile::updatePosition(float dt, TileType** tiles, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies) {
	setPosition(getPosition() + velocity * dt);
	sf::Vector2f checkPoint = position;
	for (int i = 0; i < enemies.size(); i++) {
		if (checkPoint.x > enemies[i]->getPosition().x - enemies[i]->getSize().x/2
			&& checkPoint.y > enemies[i]->getPosition().y - enemies[i]->getSize().y/2
			&& checkPoint.x < enemies[i]->getPosition().x + enemies[i]->getSize().x/2
			&& checkPoint.y < enemies[i]->getPosition().y + enemies[i]->getSize().y/2) {
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
}