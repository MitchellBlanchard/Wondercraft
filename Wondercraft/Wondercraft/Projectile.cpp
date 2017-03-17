#include "Projectile.hpp"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Vector2f spawn, sf::Vector2f startingPos, sf::Vector2f mouseLoc) : RectangleEntity(spawn, sf::Vector2f(1.5,2.5)) {
	
	//spawn is the player position, relative to the map, in tile units
	//mouseLoc will be the position of the mouse, in pixels, relative to the window
	//we need the position relative to the map to draw the player
	sf::Vector2f diffVector;
	
	//sf::playerCoor
	
	std::cout << "starting vec x:  " << startingPos.x <<  ", starting vec y:     " << startingPos.y << std::endl;
	std::cout << "spawn vec x: " << spawn.x <<    ", spawn vec y: " << spawn.y << std::endl;
	std::cout << "mouse vec x: " << mouseLoc.x << ", mouse vec y: " << mouseLoc.y << std::endl;
	//std::cout << "vel vec x:   " << velocity.x << ", vel vec y:      " << velocity.y << std::endl;

	

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