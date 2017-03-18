#include "Projectile.hpp"

#include <vector>
#include <cmath>
#include <iostream>

#include "TileType.hpp"
#include "Enemy.hpp"
#include "Model.hpp"
//#include "Collisions.hpp"

Projectile::Projectile(sf::Vector2f spawn, sf::Vector2f startingPos, sf::Vector2f playerVec, sf::Vector2f mouseLoc, float TILE_SIZE, int projectileType, bool facingRight) : RectangleEntity(spawn, sf::Vector2f(1.125,0.375)), projectileType(projectileType), TILE_SIZE(TILE_SIZE), startingPos(startingPos){
	originSize = sf::Vector2f(1.125, 0.375);
	
	mouseVector = sf::Vector2f((float)mouseLoc.x*(float)TILE_SIZE, (float)mouseLoc.y*(float)TILE_SIZE);
	
	this->mouseLoc = mouseLoc;

	diffVector = mouseVector - playerVec;
	 
	magnitude = sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));

	setBehaviour(facingRight);
}

void Projectile::update(float deltaTime, Model* model) {
	if (projectileType == FIREBALL) {
		//check collisions with entities
		//bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, std::vector<Entity*>& stillEntities, std::vector<Entity*>& collidedEntities);

		for (int i = 0; i < model->enemies.size(); i++) {
			bool collided = checkAABB(*model->enemies[i]);
			
			if (collided) {
				//we have a collision with the enemy
				Enemy* currentEnemy = dynamic_cast <Enemy*>(model->enemies[i]);

				currentEnemy->health -= damage;

				if (currentEnemy->health <= 0) {
					//remove the enemy
					for (int x = 0; x < model->enemies.size(); x++) {
						if (model->enemies[x] == currentEnemy) {
							model->enemies.erase(model->enemies.begin() + x);
						}
					}
				}
				
				//erase the projectile
				bool removed = false;;
				bool player = true;;

				for (int j = 0; j < model->playerProjectiles.size(); j++) {
 					if (model->playerProjectiles[j] == this) {
						model->playerProjectiles.erase(model->playerProjectiles.begin() + j);
						removed = true;
						break;
					}
				}

				if (!removed) {
					for (int k = 0; k < model->enemyProjectiles.size(); k++) {
						if (model->enemyProjectiles[k] == this) {
							model->enemyProjectiles.erase(model->enemyProjectiles.begin() + k);
							break;
						}
					}
				}
			}
		}

		setPosition(position + velocity*deltaTime);

		//check collisions with tiles
		//bool Collisions::collisionCalc(float& step, float deltaTime, Entity& movingEntity, Entity*** stillEntities, int cols, int rows) {

	}
}

void Projectile::explode() {
	setSize(sf::Vector2f(getSize().x + 0.05, getSize().y + 0.05));
	//std::cout << "Size: " << getSize().x << " : " << getSize().y << std::endl;
}

void Projectile::setBehaviour(bool facingRight) {
	if (projectileType == FIREBALL) {

		damage = 5;

		if (facingRight) {
			rotation = 0;
			velocity = sf::Vector2f(7, 0);
		}
		else {
			rotation = 180;
			velocity = sf::Vector2f(-7, 0);
		}
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