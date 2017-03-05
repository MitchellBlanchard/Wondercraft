#include "Projectile.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Vector2f spawn) {
	float width = 1.5;
	float height = 2.5;
	rx = width / 2;
	ry = height / 2;

	setPosition(spawn);
	velocity.x = 5;
}

bool Projectile::updatePosition(float dt, TileType** tiles, int tilesWidth, int tilesHeight, std::vector<Enemy*>& enemies) {
	move(velocity * dt);
	sf::Vector2f checkPoint = getPosition();
	for (int i = 0; i < enemies.size(); i++) {
		if (checkPoint.x > enemies[i]->getPosition().x - enemies[i]->rx
			&& checkPoint.y > enemies[i]->getPosition().y - enemies[i]->ry
			&& checkPoint.x < enemies[i]->getPosition().x + enemies[i]->rx
			&& checkPoint.y < enemies[i]->getPosition().y + enemies[i]->ry) {
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