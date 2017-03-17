#include "Projectile.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Vector2f spawn, sf::Vector2f startingPos, sf::Vector2f playerVec, sf::Vector2f mouseLoc, float TILE_SIZE, int projectileType) : RectangleEntity(spawn, sf::Vector2f(1.5,2.5)), projectileType(projectileType), TILE_SIZE(TILE_SIZE), startingPos(startingPos){
	mouseVector = sf::Vector2f((float)mouseLoc.x*(float)TILE_SIZE, (float)mouseLoc.y*(float)TILE_SIZE);
	
	this->mouseLoc = mouseLoc;

	diffVector = mouseVector - playerVec;
	 
	magnitude = sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));

	setBehaviour();
}

void Projectile::update(float deltaTime, Model* model) {
	if (projectileType == FIREBALL) { 
		position += (velocity * deltaTime);
	}
	else if (projectileType == FIRE_BOMB) {
		sf::Vector2f relativePos = sf::Vector2f(((-startingPos.x)*TILE_SIZE) + (position.x * TILE_SIZE), ((position.y * TILE_SIZE) - (startingPos.y*TILE_SIZE)));

		sf::Vector2f distance = mouseVector - relativePos;
		//std::cout << abs(distance.x) << " : " << abs(distance.y) << std::endl;

		if (abs(distance.x) > 5 || abs(distance.y) > 5) {
			position += (velocity * deltaTime);
		}
		else {
			//start the expansion of the bomb
			explode();
		}
 
	}
	
}

void Projectile::explode() {
	//nothing yet
}

void Projectile::setBehaviour() {
	if (projectileType == FIREBALL) {

		velocity = sf::Vector2f((diffVector.x / magnitude) * 5, (diffVector.y / magnitude) * 5);
	}
	else if (projectileType == FIRE_BOMB) {

		velocity = sf::Vector2f((diffVector.x / magnitude) * 5, (diffVector.y / magnitude) * 5);
	}
}

/*
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
}*/