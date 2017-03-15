#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f spawn) : RectangleEntity(spawn - sf::Vector2f(2.5/2, 1.5/2), sf::Vector2f(2.5,1.5)) {
}

void Enemy::updatePosition(float dt, Player* player) {
	position += (velocity * dt);
}