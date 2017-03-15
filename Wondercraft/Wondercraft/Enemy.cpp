#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f spawn) {
	sf::Vector2f dim(2.5, 1.5);
	rx = dim.x / 2;
	ry = dim.y / 2;
	setPosition(spawn.x - rx, spawn.y - ry);
}

void Enemy::updatePosition(float dt, Player* player) {
	move(velocity * dt);
}