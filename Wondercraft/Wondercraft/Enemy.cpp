#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f spawn, int type, float TILE_SIZE) : RectangleEntity(spawn - sf::Vector2f(2.5/2, 1.5/2), sf::Vector2f(2.5,1.5)), TILE_SIZE(TILE_SIZE) {
	if (type == 1) {
		//we need to spawn a goober
		this->type = EnemyType::GOOBER;
		health = 15;
		damage = 10;
	}
	else if (type == 2) {
		//we need to spawn a ghost
		this->type = EnemyType::GHOST;
		health = 10;
		damage = 7;
	}
	else if (type == 3) {
		//we need to spawn a goblin
		this->type = EnemyType::GOBLIN;
		health = 10;
		damage = 7;
	}
}

void Enemy::updatePosition(float dt, Player* player) {
	std::cout << type << std::endl;
	if (type == EnemyType::GOOBER) {
		//move like a goober
		//setPosition(getPosition() + velocity * dt);
	}
	else if (type == EnemyType::GHOST) {
		//move like a ghost
		sf::Vector2f ghostVec = sf::Vector2f(position.x*TILE_SIZE, position.y*TILE_SIZE);
		sf::Vector2f playerVec = sf::Vector2f(player->getPosition().x*TILE_SIZE, player->getPosition().y*TILE_SIZE);
		sf::Vector2f diffVector = ghostVec - playerVec;

		float magnitude = sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));

		velocity = sf::Vector2f(-(diffVector.x / magnitude) * 2, -(diffVector.y / magnitude) * 2);

		setPosition(position + velocity*dt);
		std::cout << position.x << " : " << position.y << std::endl;
	}
	else if (type == EnemyType::GOBLIN) {
		//move like a goblin
	}
	
}