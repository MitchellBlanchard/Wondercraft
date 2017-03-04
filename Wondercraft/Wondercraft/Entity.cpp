#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f dim) {
	rx = dim.x / 2;
	ry = dim.y / 2;
	setPosition(pos.x - rx, pos.y - ry);
}

void Enemy::updatePosition(float dt, Player* player) {
	move(velocity * dt);
}