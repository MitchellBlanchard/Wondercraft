#include "Player.hpp"

Player::Player(sf::Vector2f spawn){
	float width = 1.5;
	float height = 2.5;
	rx = width / 2;
	ry = height / 2;

	setPosition(spawn);
}

void Player::updatePosition(float dt, TileType**) {
	//for(int xWall = getPosition().x)
}