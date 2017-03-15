#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f spawn) : Entity(spawn){
	sf::Vector2f dim(2.5, 1.5);
	size.x = 2.5;
	size.y = 1.5;

	position = sf::Vector2f(spawn.x - (size.x/2), spawn.y - (size.y/2));
}

void Enemy::updatePosition(float dt, Player* player) {
	position += (velocity * dt);
}

float Enemy::collisionCalc(float deltaTime, Entity&) {
	//placeholder for the actual collisio calc function
	return -1.0f;
}
